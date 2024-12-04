// BasicTransformation.h
#pragma once
#include <glm/glm.hpp>

class BasicTransformation {
public:
    virtual ~BasicTransformation() = default;
    virtual glm::mat4 apply(const glm::mat4& model) const = 0;
};
