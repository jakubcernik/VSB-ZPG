#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <memory> // Pro použití std::shared_ptr
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include <iostream>

class DrawableObject {
private:
    std::shared_ptr<Model> model;  // Použití shared_ptr na Model
    ShaderProgram shaderProgram;
    Transformation transform;

public:
    DrawableObject(std::shared_ptr<Model> mod, const ShaderProgram& shader);
    void draw();
    void setTransformation(const Transformation& trans);
};

#endif // DRAWABLEOBJECT_H
