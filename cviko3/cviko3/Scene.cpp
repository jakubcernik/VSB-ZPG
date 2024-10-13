#include "Scene.h"

void Scene::addObject(const std::shared_ptr<DrawableObject>& object) {
    objects.push_back(object);
}

void Scene::render() {
    for (auto& object : objects) {
        object->draw();
    }
}
