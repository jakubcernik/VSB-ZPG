#pragma once
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"

class DrawableObject {
private:
    const Model* model;
    Transformation transformation;
    ShaderProgram shaderProgram;

public:
    DrawableObject(const Model& mdl, const Transformation& trans, const ShaderProgram& shader);
    void draw();
};