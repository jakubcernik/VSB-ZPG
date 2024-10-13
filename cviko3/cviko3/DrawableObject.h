#pragma once
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"

class DrawableObject {
private:
    const Model* model;
    Transformation transformation;
    ShaderProgram shaderProgram; // P�id�n� shaderu jako �lena t��dy

public:
    DrawableObject(const Model& mdl, const Transformation& trans, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void draw(const glm::mat4& projection, const glm::mat4& view);

};
