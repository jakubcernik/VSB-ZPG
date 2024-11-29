#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "DrawableObject.h"

class Camera;

class Scene {

protected:
    std::vector<DrawableObject> objects;

public:
    virtual ~Scene() = default;
    void addObject(const DrawableObject& object);
    virtual void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) = 0;
    virtual Camera& getCamera() = 0;
};
