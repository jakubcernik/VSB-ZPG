#pragma once
#include "Subject.h"
#include "SphereModel.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>

class Light : public Subject {
public:
    Light(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color, ShaderProgram& lightShader, float scale, float angle, int type);
    void setPosition(const glm::vec3& newPosition);
    void setDirection(const glm::vec3& newDirection);
    void setColor(const glm::vec3& newColor);

    const glm::vec3& getPosition() const;
    const glm::vec3& getColor() const;

    const glm::vec3 getDirection() const;
    float getAngle() const;
    int getType() const;

    void draw() const;

private:
    glm::vec3 position;
    glm::vec3 color;
    SphereModel lightModel;
    ShaderProgram& lightShader;
    float scale;

    glm::vec3 direction;
    float angle;
    int type;
};
