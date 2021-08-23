#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cstdint>
#include <future>

#include "oiio/include/OpenImageIO/imageio.h"

std::uint32_t const kNumberOfChannels = 3;
const auto imm8 = 0b1111'0001;

struct ray
{
	float ox, oy, oz;
	float dx, dy, dz;
	float maxt;
};

struct sphere
{
	float cx, cy, cz;
	float radius;
	float rgb[kNumberOfChannels];
};

struct sphereCalculations
{
	float radiusSquared;
	__m128 m128;
};

std::uint32_t const kImageWidth = 2048;
std::uint32_t const kImageHeight = 2048;
std::uint32_t const kNumSpheres = 512;

#define RAND_FLOAT (((float)std::rand()) / RAND_MAX)
#define LEFT -10.f
#define BOTTOM -10.f
#define WIDTH 20.f
#define HEIGHT 20.f
#define NEAR -10.f
#define FAR 10.f

void generate_spheres(sphere* spheres, std::uint32_t num_spheres)
{
	std::srand(0x88e8fff4);

	for (auto i = 0U; i < num_spheres; ++i)
	{
		spheres[i].cx = RAND_FLOAT * 20.f - 10.f;
		spheres[i].cy = RAND_FLOAT * 20.f - 10.f;
		spheres[i].cz = RAND_FLOAT * 20.f - 5.f;
		spheres[i].radius = (RAND_FLOAT + 0.1f) * 1.5f;
		spheres[i].rgb[0] = RAND_FLOAT;
		spheres[i].rgb[1] = RAND_FLOAT;
		spheres[i].rgb[2] = RAND_FLOAT;
	}
}

//removed "solve_quadratic"

// Intersect the ray against the sphere
// If there is an intersection:
// * return true
// * update r.maxt to intersection distance
bool intersect_sphere(const sphereCalculations& sphereCalc, ray& r, const __m128& m128_0, const float a)
{
	//refactored with sse instructions
	__m128 m128_1 = _mm_set_ps(r.ox, r.oy, r.oz, 0);

	m128_1 = _mm_sub_ps(m128_1, sphereCalc.m128);

	const float b = _mm_dp_ps(m128_0, m128_1, imm8).m128_f32[0] * 2;
	const float c = _mm_dp_ps(m128_1, m128_1, imm8).m128_f32[0] - sphereCalc.radiusSquared;

	const float d = b * b - 4 * a * c;

	if(d >= 0)
	{
		//inserted code from function "solve_quadratic"
		const float den = 1 / (2 * a);
		//small optimizations
		const auto root = std::sqrt(d);
		const float x1 = (-b - root) * den;
		const float x2 = (-b + root) * den;

		if(x1 <= r.maxt && x2 >= 0.f)
		{
			r.maxt = x1 > 0.f ? x1 : x2;
			return true;
		}
	}
	return false;
}


// Render the image img usign ray tracing for ortho projection camera
void trace(sphere const* spheres, std::uint32_t num_spheres, const sphereCalculations* sphereCalcs, float* img, std::uint32_t imgFrom, std::uint32_t imgTo)
{
	ray r;
	r.oz = NEAR;
	r.dx = r.dy = 0.f;
	r.dz = 1.f;

	//took out some calculations from inner loop
	const __m128 m128_0 = _mm_set_ps(r.dx, r.dy, r.dz, 0);
	const float a = _mm_dp_ps(m128_0, m128_0, imm8).m128_f32[0];

	float oxCalcs[kImageWidth];
	for(size_t i = 0; i < kImageWidth; ++i)
	{
		oxCalcs[i] = LEFT + (WIDTH / kImageWidth) * (i + 0.5f);
	}

	img += imgFrom * kImageWidth * kNumberOfChannels;
	const auto imgHeight = imgFrom + imgTo;
	for(auto j = imgFrom; j < imgHeight; ++j)
	{
		//take out some calculations from inner loop
		r.oy = BOTTOM + (HEIGHT / kImageHeight) * (j + 0.5f);
		for (auto i = 0U; i < kImageWidth; ++i)
		{
			r.ox = oxCalcs[i];
			r.maxt = FAR - NEAR;

			//replaced index to more significant data type
			const sphere* sphere = nullptr;
			for (auto k = 0U; k < num_spheres; ++k)
			{
				if (intersect_sphere(sphereCalcs[k], r, m128_0, a))
				{
					sphere = spheres + k;
				}
			}

			//optimized copying data
			if(sphere)
			{
				memcpy(img, sphere->rgb, sizeof(sphere->rgb));
			}

			img += kNumberOfChannels;
		}
	}
}

void trace_parallel(sphere const* spheres, std::uint32_t num_spheres, float* img)
{
	//precalculate a lookup table for spheres to avoid superfluous calculations through iterations
	std::vector<sphereCalculations> sphereCalcs(num_spheres);
	for(auto i = 0; i < num_spheres; ++i)
	{
		const sphere* sph = spheres + i;
		sphereCalculations& sphereCalc = sphereCalcs[i];

		sphereCalc.m128 = _mm_set_ps(sph->cx, sph->cy, sph->cz, 0);
		sphereCalc.radiusSquared = sph->radius * sph->radius;
	}

	//create number of threads equal to available on current hardware
	const auto threadsNumber = std::thread::hardware_concurrency();
	const auto deltaHeight = kImageHeight / threadsNumber;
	std::vector<std::thread> tasks;
	tasks.reserve(threadsNumber);
	//splite the picture into rows and handle them in threads
	for(auto i = 0; i < threadsNumber; ++i)
	{
		auto task = std::thread(trace, spheres, num_spheres, sphereCalcs.data(), img, deltaHeight * i, deltaHeight);
		tasks.push_back(std::move(task));
	}
	for(auto& task : tasks)
	{
		task.join();
	}
}

int main()
{
	std::vector<sphere> spheres(kNumSpheres);

	generate_spheres(&spheres[0], kNumSpheres);

	std::vector<float> img(kImageWidth * kImageHeight * kNumberOfChannels, 0.1f);

	auto start = std::chrono::high_resolution_clock::now();

	trace_parallel(&spheres[0], kNumSpheres, img.data());

	auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();

	std::cout << "Execution time " << delta << " ms\n";

	OIIO_NAMESPACE_USING;

	ImageOutput* out = ImageOutput::create("result.png");

	if (!out)
	{
		std::cout << "Can't create image file on disk";
		return -1;
	}

	ImageSpec spec(kImageWidth, kImageHeight, 3, TypeDesc::FLOAT);

	out->open("result.png", spec);
	out->write_image(TypeDesc::FLOAT, img.data(), sizeof(float) * kNumberOfChannels);
	out->close();

	return 0;
}
