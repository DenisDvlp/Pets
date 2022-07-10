#include "Scene.h"
#include "Drawing.h"
#include "Vector4.h"
#include "Camera.h"
#include "Drawable.h"

void Scene::setCamera(Camera& camera)
{
  this->camera = &camera;
}

void Scene::addDrawable(Drawable& drawable)
{
  drawables.push_back(&drawable);
}

void Scene::resize(int width, int height)
{
  aspect = (float)width / height;
  glViewport(0, 0, width, height);
}

void Scene::init()
{
  const Color clearColor = { 0.5f, 0.5f, 0.5f, 0 };
  const Color ambient; // {0,0,0,0}

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glClearColor(clearColor.r(), clearColor.g(), clearColor.b(), clearColor.a());
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);

  for (Drawable* drawable : drawables)
  {
    drawable->init();
  }
}

void Scene::draw() const
{
  clear();
  if (camera)
  {
    camera->draw();
  }
  for (const Drawable* drawable : drawables)
  {
    drawable->draw(*quadric);
  }
}

void Scene::clear() const
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0f, aspect, 0.01f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
