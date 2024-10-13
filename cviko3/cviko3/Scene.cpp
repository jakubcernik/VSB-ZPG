#include "Scene.h"

void Scene::addObject(const DrawableObject& object) {
    objects.push_back(object);
}

void Scene::render() {
    for (auto& object : objects) {
        object.draw();
    }
}
