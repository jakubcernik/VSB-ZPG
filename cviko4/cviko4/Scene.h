#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "DrawableObject.h"

class Scene {
protected:
    std::vector<DrawableObject> objects;

public:
    virtual ~Scene() = default;
    void addObject(const DrawableObject& object);
    virtual void render() = 0;
};
