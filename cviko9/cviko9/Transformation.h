// Transformation.h
#pragma once
#include "BasicTransformation.h"
#include <vector>
#include <memory>

class Transformation : public BasicTransformation {
public:
    Transformation& addTransformation(std::shared_ptr<BasicTransformation> transformation);

    glm::mat4 apply(const glm::mat4& model) const override;
    // Pridat getmatrix ktera vrati matici
    // Pridat dynamickou rotaci, musi byt tady uvnitr tridy a ne tak ze vytvarim objekty s upravenou transformaci (rotatingTrees)

private:
    std::vector<std::shared_ptr<BasicTransformation>> transformations;
};