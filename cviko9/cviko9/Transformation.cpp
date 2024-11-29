// Transformation.cpp
#include "Transformation.h"

Transformation& Transformation::addTransformation(std::shared_ptr<BasicTransformation> transformation) {
    transformations.push_back(transformation);
    return *this; // Vr�t� aktu�ln� instanci, aby �lo �et�zit vol�n�
}

glm::mat4 Transformation::apply(const glm::mat4& model) const {
    glm::mat4 result = model;
    for (const auto& transformation : transformations) {
        result = transformation->apply(result);
    }
    return result;
}
