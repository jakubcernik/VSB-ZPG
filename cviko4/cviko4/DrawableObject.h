// DrawableObject.h
#pragma once
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"

class DrawableObject {
private:
    const Model* model;
    Transformation transformation;
    ShaderProgram& shaderProgram; // Pøímý odkaz na ShaderProgram

public:
    DrawableObject(const Model& mdl, const Transformation& trans, ShaderProgram& shaderProgram);
    void draw(const glm::mat4& projection) const;
};
