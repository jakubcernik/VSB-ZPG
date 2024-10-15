#include "Scene.h"

void Scene::addObject(const DrawableObject& object) {
    objects.push_back(object);
}

void Scene::render(const glm::mat4& projection) {
    for (auto& object : objects) {
        object.draw(projection);
    }
}

