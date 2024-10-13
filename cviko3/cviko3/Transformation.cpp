#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

// Konstruktor
Transformation::Transformation()
    : translationMatrix(glm::mat4(1.0f)),
    scaleMatrix(glm::mat4(1.0f)),
    rotationMatrix(glm::mat4(1.0f)) {}

// Nastavení matic pro jednotlivé transformace
void Transformation::translate(float x, float y, float z) {
    translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void Transformation::scale(float sx, float sy, float sz) {
    scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(sx, sy, sz));
}

void Transformation::rotate(float angle, float x, float y, float z) {
    rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(x, y, z));
}

// Získání výsledné matice kombinací všech matic
glm::mat4 Transformation::getMatrix() const {
    return translationMatrix * rotationMatrix * scaleMatrix;
}
