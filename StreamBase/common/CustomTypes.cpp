#include "CustomTypes.h"
#include <iostream>

//Object_1

size_t Object_1::serializedSize()
{
	return sizeof(x);
}

std::vector<char> Object_1::serialize()
{
	const auto ptr = reinterpret_cast<char*>(x);
	return std::vector<char>(ptr, ptr + sizeof(x));
}

void Object_1::deserialize(void* data, size_t size)
{
	memcpy(x, data, sizeof(x));
}

void Object_1::print()
{
	std::cout << "Object_1:" << x[0] << std::endl;
}

//Object_2

size_t Object_2::serializedSize()
{
	return sizeof(x);
}

std::vector<char> Object_2::serialize()
{
	const auto ptr = reinterpret_cast<char*>(x);
	return std::vector<char>(ptr, ptr + sizeof(x));
}

void Object_2::deserialize(void* data, size_t size)
{
	memcpy(x, data, sizeof(x));
}

void Object_2::print()
{
	std::cout << "Object_2:" << x[0] << "," << x[1] << std::endl;
}

//Object_3

size_t Object_3::serializedSize()
{
	return sizeof(x) + (s.empty() ? 0 : s.size() + 1);
}
std::vector<char> Object_3::serialize()
{
	const auto ptr = reinterpret_cast<char*>(x);
	std::vector<char> data(ptr, ptr + sizeof(x));

	if (!s.empty())
	{
		data.insert(data.end(), s.begin(), s.end());
		data.push_back(0);
	}

	return data;
}
void Object_3::deserialize(void* data, size_t size)
{
	//fill an array of ints
	const size_t xSizeInBytes = sizeof(x);
	memcpy(x, data, xSizeInBytes);

	//shift the pointer to the next field
	data = reinterpret_cast<char*>(data) + xSizeInBytes;
	size -= xSizeInBytes;

	//fill a string
	s.clear();
	if (size > 1)
	{
		const auto ptr = reinterpret_cast<char*>(data);
		s.assign(ptr, ptr + size);
	}
}

void Object_3::print()
{
	std::cout << "Object_3:" << x[0] << "," << x[1] << "," << x[2] << "," << s << std::endl;
}
