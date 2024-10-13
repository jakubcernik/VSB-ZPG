#include "DrawableObject.h"

DrawableObject::DrawableObject(const Model& mdl, const Transformation& trans, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    : model(&mdl), transformation(trans), shaderProgram(vertexShaderPath, fragmentShaderPath) {}

void DrawableObject::draw(const glm::mat4& projection, const glm::mat4& view) {
    shaderProgram.use();

    // Pøedání matic shaderu
    shaderProgram.setUniform("projection", projection);
    shaderProgram.setUniform("view", view);
    shaderProgram.setUniform("model", transformation.getModelMatrix());

    model->draw();
}
