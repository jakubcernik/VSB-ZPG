// Translation.h
#pragma once
#include "BasicTransformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Translation : public BasicTransformation {
public:
    Translation(const glm::vec3& deltaPosition);
    glm::mat4 apply(const glm::mat4& model) const override;
private:
    glm::vec3 deltaPosition;
};