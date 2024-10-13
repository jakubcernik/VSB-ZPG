#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation()
    : position(0.0f), rotation(0.0f), scale(1.0f) {}

glm::mat4 Transformation::getModelMatrix() const {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    // Další transformace podle rotace a mìøítka
    return model;
}
