#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation() {}

Transformation::~Transformation() {
    for (auto* transformation : transformations) {
        delete transformation;
    }
}

Transformation& Transformation::addTransformation(BasicTransformation* transformation) {
    transformations.push_back(transformation);
    return *this;
}

glm::mat4 Transformation::apply(const glm::mat4& model) const {
    glm::mat4 result = model;
    for (const auto* transformation : transformations) {
        result = transformation->apply(result);
    }
    return result;
}

glm::mat4 Transformation::getMatrix() const {
    return apply(glm::mat4(1.0f));
}

// Inner class for dynamic rotation
class DynamicRotation : public BasicTransformation {
public:
    DynamicRotation(float* anglePointer, const glm::vec3& axis)
        : anglePointer(anglePointer), axis(axis) {}

    glm::mat4 apply(const glm::mat4& model) const override {
        return glm::rotate(model, glm::radians(*anglePointer), axis);
    }

private:
    float* anglePointer;
    glm::vec3 axis;
};

void Transformation::addDynamicRotation(float* anglePointer, const glm::vec3& axis) {
    transformations.push_back(new DynamicRotation(anglePointer, axis));
}
