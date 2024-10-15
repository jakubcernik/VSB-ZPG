#include "DrawableObject.h"

DrawableObject::DrawableObject(const Model& mdl, const Transformation& trans, ShaderProgram& shaderProgram)
    : model(&mdl), transformation(trans), shaderProgram(shaderProgram) {}


void DrawableObject::draw(const glm::mat4& projection) {
    shaderProgram.use();

    shaderProgram.setUniform("projection", projection); // Pøedáváme jen projekci
    shaderProgram.setUniform("model", transformation.getModelMatrix());
    

    model->draw();
}
