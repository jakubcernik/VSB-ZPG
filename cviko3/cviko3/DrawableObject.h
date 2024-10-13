#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject {
private:
    Model model;
    ShaderProgram shaderProgram;
    Transformation transform;

public:
    DrawableObject(const Model& mod, const ShaderProgram& shader);
    void draw();
    void setTransformation(const Transformation& trans);
};

#endif // DRAWABLEOBJECT_H
