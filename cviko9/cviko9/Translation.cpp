// Translation.cpp
#include "Translation.h"

Translation::Translation(const glm::vec3& deltaPosition) : deltaPosition(deltaPosition) {}

glm::mat4 Translation::apply(const glm::mat4& model) const {
    return glm::translate(model, deltaPosition);
}
