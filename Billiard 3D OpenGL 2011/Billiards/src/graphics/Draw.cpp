#include "graphics/Draw.hpp"
#include <cassert>
#include <gl/gl.h>
#include <gl/glu.h>

namespace gl {

static GLUquadric* guadric{gluNewQuadric()};

namespace camera {

void init(const std::uint8_t* backgroundColor) {
    gluQuadricNormals(guadric, GLU_SMOOTH);
    gluQuadricTexture(guadric, GL_TRUE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    constexpr float kMaxVolorValue{255};
    glClearColor(backgroundColor[0] / kMaxVolorValue, backgroundColor[1] / kMaxVolorValue,
                 backgroundColor[2] / kMaxVolorValue, backgroundColor[3] / kMaxVolorValue);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    constexpr float ambient[4]{};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
}

void clear(const float angle, const float aspect, const float nearDistance, const float farDistance) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, aspect, nearDistance, farDistance);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void resize(const std::uint16_t width, const std::uint16_t height) {
    glViewport(0, 0, width, height);
}

} // namespace camera

namespace color {

void rgba(const std::uint8_t* color) {
    glColor4ubv(color);
}

void rgb(const std::uint8_t* color) {
    glColor3ubv(color);
}

} // namespace color

namespace material {

void reflection(float intensity, float sharpness) {
    const float color[] = {intensity, intensity, intensity, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, color);
    const float shininess = 128.0f * sharpness;
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
}

void glow(float intensity) {
    const float color[] = {intensity, intensity, intensity, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
}

void diffusion(float intensity) {
    const float color[] = {intensity, intensity, intensity, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
}

void ambient(float intensity) {
    const float color[] = {intensity, intensity, intensity, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, color);
}

} // namespace material

namespace light {

unsigned int availableId() {
    static unsigned int availableLightId{GL_LIGHT0};
    assert((availableLightId >= GL_MAX_LIGHTS) && "Limit of number of lights is reached.");
    return availableLightId++;
}

void turn(int id, bool on) {
    on ? glEnable(id) : glDisable(id);
}

void ambient(int id, float intensity) {
    const float color[] = {intensity, intensity, intensity, 1.0f};
    glLightfv(id, GL_AMBIENT, color);
}

void diffusion(int id, float intensity) {
    const float color[] = {intensity, intensity, intensity, 1.0f};
    glLightfv(id, GL_DIFFUSE, color);
}

void reflection(int id, float intensity) {
    const float color[] = {intensity, intensity, intensity, 1.0f};
    glLightfv(id, GL_SPECULAR, color);
}

void spotAngle(int id, float angle) {
    glLightf(id, GL_SPOT_CUTOFF, angle);
}

void direction(int id, const float* xyz, bool isSpot) {
    if (isSpot) {
        static constexpr float xyzs[] = {0, 0, 0, 1.0f};
        glLightfv(id, GL_POSITION, xyzs);
        glLightfv(id, GL_SPOT_DIRECTION, xyz);
    } else {
        glLightfv(id, GL_POSITION, xyz);
    }
}

} // namespace light

namespace transform {

void position(const float* xyz) {
    glTranslatef(xyz[0], xyz[1], xyz[2]);
}

void position(float x, float y, float z) {
    glTranslatef(x, y, z);
}

void rotation(const float* xyz) {
    glRotatef(xyz[0], 1, 0, 0);
    glRotatef(xyz[1], 0, 1, 0);
    glRotatef(xyz[2], 0, 0, 1);
}

void rotationX(const float angle) {
    glRotatef(angle, 1, 0, 0);
}

void rotationY(const float angle) {
    glRotatef(angle, 0, 1, 0);
}

void rotationZ(const float angle) {
    glRotatef(angle, 0, 0, 1);
}

} // namespace transform

namespace figure {

void sphere(const float radius, const int verPolygons, const int horPolygons) {
    gluSphere(guadric, 0.068f, 64, 64);
}

void cylinder(const float baseRadius, const float topRadius, const float height, const int verPolygons,
              const int horPolygons) {
    gluCylinder(guadric, baseRadius, topRadius, height, verPolygons, horPolygons);
}

void disk(const float innerRadius, const float outerRadius, const int verPolygons, const int horPolygons) {
    gluDisk(guadric, innerRadius, outerRadius, verPolygons, horPolygons);
}

void square(const float sideLength, const int verPolygons, const int horPolygons) {
    const float dx{sideLength / horPolygons};
    const float dy{sideLength / verPolygons};
    glBegin(GL_QUADS);
    float start{-sideLength / 2};
    float stop{-start};
    for (float y{start}; y < stop; y += dy) {
        for (float x{start}; x < stop; x += dx) {
            glVertex3f(x, y, 0);
            glVertex3f(x, y + dy, 0);
            glVertex3f(x + dx, y + dy, 0);
            glVertex3f(x + dx, y, 0);
        }
    }
    glEnd();
}

} // namespace figure

namespace guard {

MaterialGuard::MaterialGuard() {
    glPushAttrib(GL_LIGHTING_BIT);
}

MaterialGuard::~MaterialGuard() {
    glPopAttrib();
}

MatrixGuard::MatrixGuard() {
    glPushMatrix();
}

MatrixGuard::~MatrixGuard() {
    glPopMatrix();
}

} // namespace guard

} // namespace gl
