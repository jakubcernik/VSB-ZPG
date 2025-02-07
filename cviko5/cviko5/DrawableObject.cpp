// DrawableObject.cpp

#define GLM_ENABLE_EXPERIMENTAL
#include "DrawableObject.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

DrawableObject::DrawableObject(const Model& mdl, const Transformation& trans, ShaderProgram& shaderProgram, bool isTreeObject, const glm::vec3& color)
    : model(&mdl), transformation(trans), shaderProgram(shaderProgram), isTreeObject(isTreeObject), color(color) {}

void DrawableObject::draw() const {
    glm::mat4 modelMatrix = transformation.apply(glm::mat4(1.0f));
    shaderProgram.setUniform("modelMatrix", modelMatrix);
    model->draw();
}
