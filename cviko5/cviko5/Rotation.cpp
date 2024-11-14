// Rotation.cpp

#include "Rotation.h"
#include <glm/gtc/matrix_transform.hpp>

// Konstruktor
Rotation::Rotation(float angleX, float angleY, float angleZ)
    : angleX(angleX), angleY(angleY), angleZ(angleZ) {}

// Aplikace rotace na matici
glm::mat4 Rotation::apply(const glm::mat4& model) const {
    glm::mat4 rotatedModel = glm::rotate(model, glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));
    rotatedModel = glm::rotate(rotatedModel, glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));
    rotatedModel = glm::rotate(rotatedModel, glm::radians(angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
    return rotatedModel;
}
