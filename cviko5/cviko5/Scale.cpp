// Scale.cpp
#include "Scale.h"

// Constructor and apply method are already defined in the header file
Scale::Scale(const glm::vec3& scale) : scale(scale) {}

glm::mat4 Scale::apply(const glm::mat4& model) const {
    return glm::scale(model, scale);
}
