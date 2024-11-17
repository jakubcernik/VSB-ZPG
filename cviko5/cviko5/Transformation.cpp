// Transformation.cpp
#include "Transformation.h"

void Transformation::addTransformation(std::shared_ptr<BasicTransformation> transformation) {
    transformations.push_back(transformation);
}

glm::mat4 Transformation::apply(const glm::mat4& model) const {
    glm::mat4 result = model;
    for (const auto& transformation : transformations) {
        result = transformation->apply(result);
    }
    return result;
}
