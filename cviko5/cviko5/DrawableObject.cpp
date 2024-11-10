//DrawableObject.cpp

#define GLM_ENABLE_EXPERIMENTAL
#include "DrawableObject.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>


DrawableObject::DrawableObject(const Model& mdl, const Transformation& trans, ShaderProgram& shaderProgram, bool isTreeObject, const glm::vec3& color)
    : model(&mdl), transformation(trans), shaderProgram(shaderProgram), isTreeObject(isTreeObject), color(color) {}



void DrawableObject::draw() const {
    glm::mat4 modelMatrix = transformation.getModelMatrix();

    shaderProgram.use();
    
    shaderProgram.setUniform("modelMatrix", modelMatrix);
    //setModelTransform(T) je lepsi poslat primo instanci transformace, az shaderProgram se rozhodne co s tim delat, zodpovednost prechazi na shader
    
    shaderProgram.use();

    model->draw();
}
