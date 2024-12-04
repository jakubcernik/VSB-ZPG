// Light.cpp

#include "Light.h"
#include "Transformation.h"
#include "Translation.h"
#include "Scale.h"

Light::Light(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color, ShaderProgram& lightShader, float scale, float angle, int type)
    : position(position), direction(direction), color(color), lightShader(lightShader), scale(scale), angle(angle), type(type) {}

void Light::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
    notifyObservers(glm::mat4(1.0f), glm::mat4(1.0f)); // viewMatrix and projectionMatrix
}

void Light::setDirection(const glm::vec3& newDirection) {
	direction = newDirection;
	notifyObservers(glm::mat4(1.0f), glm::mat4(1.0f)); // viewMatrix and projectionMatrix
}

void Light::setColor(const glm::vec3& newColor) {
    color = newColor;
    notifyObservers(glm::mat4(1.0f), glm::mat4(1.0f)); // viewMatrix and projectionMatrix
}

const glm::vec3& Light::getPosition() const {
    return position;
}

const glm::vec3& Light::getColor() const {
    return color;
}

glm::vec3 Light::getDirection() const {
    return direction;
}

float Light::getAngle() const {
    return angle;
}

int Light::getType() const {
    return type;
}

void Light::draw() const {
    Transformation transform;  // Create a Transformation object on the stack

    // Add transformations using raw pointers
    transform.addTransformation(new Translation(position));
    transform.addTransformation(new Scale(glm::vec3(scale)));

    glm::mat4 modelMatrix = transform.apply(glm::mat4(1.0f));
    lightShader.use();
    lightShader.setUniform("modelMatrix", modelMatrix);
    lightModel.draw();
    lightShader.free();
    // No need to delete 'transform', as it will be destroyed automatically when it goes out of scope
}


