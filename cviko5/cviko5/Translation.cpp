// Translation.cpp
#include "Translation.h"

// Constructor and apply method are already defined in the header file
Translation::Translation(const glm::vec3& deltaPosition) : deltaPosition(deltaPosition) {}

glm::mat4 Translation::apply(const glm::mat4& model) const {
    return glm::translate(model, deltaPosition);
}
