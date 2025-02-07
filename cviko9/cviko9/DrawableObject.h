#pragma once
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"

class DrawableObject {
private:
    const Model* model;
    Transformation* transformation;
    ShaderProgram& shaderProgram;
    bool isTreeObject;
    glm::vec3 color;

public:
    DrawableObject(const Model& mdl, Transformation* trans, ShaderProgram& shaderProgram, bool isTreeObject, const glm::vec3& color);
    void draw() const;
    bool isTree() const { return isTreeObject; }
    const glm::vec3& getColor() const { return color; }
    Transformation& getTransform() { return *transformation; }
};
