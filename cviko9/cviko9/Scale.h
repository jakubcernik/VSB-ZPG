//Scale.h
#pragma once
#include "BasicTransformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Scale : public BasicTransformation {
public:
    Scale(const glm::vec3& scale);
    glm::mat4 apply(const glm::mat4& model) const override;

private:
    glm::vec3 scale;
};
