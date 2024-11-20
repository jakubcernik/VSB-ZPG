// Scale.cpp
#include "Scale.h"

Scale::Scale(const glm::vec3& scale) : scale(scale) {}

glm::mat4 Scale::apply(const glm::mat4& model) const {
    return glm::scale(model, scale);
}
