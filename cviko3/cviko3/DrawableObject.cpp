#include "DrawableObject.h"

DrawableObject::DrawableObject(const Model& mod, const ShaderProgram& shader)
    : model(mod), shaderProgram(shader) {}

void DrawableObject::draw() {
    shaderProgram.useProgram();
    model.draw();
}

void DrawableObject::setTransformation(const Transformation& trans) {
    transform = trans;
}
