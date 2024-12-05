//Transformation.h
#pragma once
#include <vector>
#include <memory>
#include "BasicTransformation.h"

class Transformation : public BasicTransformation {
public:
    Transformation();
    ~Transformation();

    Transformation& addTransformation(BasicTransformation* transformation);

    glm::mat4 apply(const glm::mat4& model) const override;
    glm::mat4 getMatrix() const;

    // Add dynamic rotation
    void addDynamicRotation(float* anglePointer, const glm::vec3& axis);

private:
    std::vector<BasicTransformation*> transformations;
};
