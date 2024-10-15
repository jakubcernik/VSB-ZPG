#define GLM_ENABLE_EXPERIMENTAL
#include "DrawableObject.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp> // Pro glm::to_string
#include <iostream> // Pro std::cout


DrawableObject::DrawableObject(const Model& mdl, const Transformation& trans, ShaderProgram& shaderProgram)
    : model(&mdl), transformation(trans), shaderProgram(shaderProgram) {}


void DrawableObject::draw(const glm::mat4& projection) {
    glm::mat4 modelMatrix = transformation.getModelMatrix();

    shaderProgram.use();

    shaderProgram.setUniform("projection", projection); // Pøedáváme jen projekci
    shaderProgram.setUniform("model", modelMatrix);

    std::cout << "Model Matrix: " << glm::to_string(modelMatrix) << std::endl;

    model->draw();
}
