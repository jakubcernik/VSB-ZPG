#include "DrawableObject.h"

DrawableObject::DrawableObject(const Model& mdl, Transformation* trans, ShaderProgram& shaderProgram, bool isTreeObject, const glm::vec3& color)
    : model(&mdl), transformation(trans), shaderProgram(shaderProgram), isTreeObject(isTreeObject), color(color) {}

void DrawableObject::draw() const {
    glm::mat4 modelMatrix = transformation->apply(glm::mat4(1.0f));
    shaderProgram.setUniform("modelMatrix", modelMatrix);
    model->draw();
}
