#include "DrawableObject.h"

DrawableObject::DrawableObject(const Model& mdl, const Transformation& trans, const ShaderProgram& shader)
    : model(&mdl), transformation(trans), shaderProgram(shader) {}

void DrawableObject::draw() {
    shaderProgram.use();
    // Nastav transformace a vykresli model
    model->draw(); // Použití ukazatele na model
}
