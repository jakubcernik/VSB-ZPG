// Light.h
#pragma once
#include "Observable.h"
#include "SphereModel.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>

class Light : public Observable {
public:
    Light(const glm::vec3& position, const glm::vec3& color, ShaderProgram& lightShader, float scale = 1.0f);
    void setPosition(const glm::vec3& newPosition);
    void setColor(const glm::vec3& newColor);

    const glm::vec3& getPosition() const;
    const glm::vec3& getColor() const;

    void draw(const glm::mat4& projection, const glm::mat4& view) const;

private:
    glm::vec3 position;
    glm::vec3 color;
    SphereModel lightModel;
    ShaderProgram& lightShader;
    float scale;
};
