//Transformation.cpp

#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation()
    : position(0.0f), rotation(0.0f), scale(1.0f) {}

void Transformation::translate(const glm::vec3& deltaPosition) {
    position += deltaPosition;
}

void Transformation::rotate(float angleX, float angleY, float angleZ) {
    rotation.x += angleX;
    rotation.y += angleY;
    rotation.z += angleZ;
}

void Transformation::setScale(const glm::vec3& newScale) {
    scale = newScale;
}

glm::mat4 Transformation::getModelMatrix() const {

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

    // Rotations for every axis
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, scale);
    return model;
}
