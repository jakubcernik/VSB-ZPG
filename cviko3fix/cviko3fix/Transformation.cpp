#define GLM_ENABLE_EXPERIMENTAL
#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Transformation::Transformation()
    : position(0.0f), rotation(0.0f), scale(1.0f) {}

void Transformation::translate(const glm::vec3& deltaPosition) {
    position += deltaPosition;
}

void Transformation::rotate(const glm::vec3& deltaRotation) {
    rotation += deltaRotation;
}

void Transformation::setScale(const glm::vec3& newScale) {
    scale = newScale;
}

glm::mat4 Transformation::getModelMatrix() const {
    // Aplikace translace
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

    // Aplikace rotace kolem os
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotace kolem osy X
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotace kolem osy Y
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotace kolem osy Z

    // Aplikace škálování
    model = glm::scale(model, scale);

    return model;
}


glm::vec3 Transformation::getPosition() const {
    return position;
}

glm::vec3 Transformation::getRotation() const {
    return rotation;
}

glm::vec3 Transformation::getScale() const {
    return scale;
}
