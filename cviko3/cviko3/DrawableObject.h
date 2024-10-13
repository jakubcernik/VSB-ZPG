#pragma once
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"

class DrawableObject {
private:
    Model model;
    Transformation transformation;
    ShaderProgram shaderProgram;

public:
    DrawableObject(const Model& mdl, const Transformation& trans, const ShaderProgram& shader);
    void draw(); // Vykreslí objekt
};
