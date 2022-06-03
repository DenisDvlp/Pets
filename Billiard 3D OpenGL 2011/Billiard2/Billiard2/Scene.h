#pragma once
#include <vector>
#include "QuadricPtr.h"

class Drawable;
class Camera;

class Scene
{
  std::vector<Drawable*> drawables;
  Camera* camera;
  float aspect; // для перспективы
  QuadricPtr quadric;
private:
  void clear() const;
public:
  void setCamera(Camera& camera);
  template<typename T>
  void addDrawables(std::vector<T>& drawables);
  void addDrawable(Drawable& drawable);
  void resize(int width, int height);
  void init();
  void draw() const;
};

template<typename T>
void Scene::addDrawables(std::vector<T>& drawables)
{
  for (Drawable& drawable : drawables)
  {
    addDrawable(drawable);
  }
}