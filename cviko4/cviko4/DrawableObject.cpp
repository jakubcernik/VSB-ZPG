//DrawableObject.cpp

#define GLM_ENABLE_EXPERIMENTAL
#include "DrawableObject.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>


DrawableObject::DrawableObject(const Model& mdl, const Transformation& trans, ShaderProgram& shaderProgram)
    : model(&mdl), transformation(trans), shaderProgram(shaderProgram) {}


void DrawableObject::draw(const glm::mat4& projection, const glm::mat4& view) const {
    glm::mat4 modelMatrix = transformation.getModelMatrix();

    shaderProgram.use();

    shaderProgram.setUniform("projection", projection);
    shaderProgram.setUniform("view", view);
    shaderProgram.setUniform("model", modelMatrix);
    
    shaderProgram.use();

    model->draw();
}
