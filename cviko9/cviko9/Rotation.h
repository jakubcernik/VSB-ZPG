// Rotation.h
#pragma once
#include "BasicTransformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Rotation : public BasicTransformation {
public:
    Rotation(float angleX, float angleY, float angleZ);
    glm::mat4 apply(const glm::mat4& model) const override;
private:
    float angleX, angleY, angleZ;
};