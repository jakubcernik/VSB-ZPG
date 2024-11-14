// Transformation.h
#pragma once
#include "BasicTransformation.h"
#include <vector>
#include <memory>

class Transformation : public BasicTransformation {
public:
    void addTransformation(std::shared_ptr<BasicTransformation> transformation);

    glm::mat4 apply(const glm::mat4& model) const override;

private:
    std::vector<std::shared_ptr<BasicTransformation>> transformations;
};