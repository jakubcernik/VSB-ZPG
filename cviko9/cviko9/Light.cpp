#include "Light.h"
#include "Transformation.h"
#include "Translation.h"
#include "Scale.h"

Light::Light(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color, ShaderProgram& lightShader, float scale, float angle, int type)
    : position(position), direction(direction), color(color), lightShader(lightShader), scale(scale), angle(angle), type(type) {}

void Light::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
    notifyObservers(glm::mat4(1.0f), glm::mat4(1.0f));
}

void Light::setDirection(const glm::vec3& newDirection) {
	direction = newDirection;
	notifyObservers(glm::mat4(1.0f), glm::mat4(1.0f));
}

void Light::setColor(const glm::vec3& newColor) {
    color = newColor;
    notifyObservers(glm::mat4(1.0f), glm::mat4(1.0f));
}

const glm::vec3& Light::getPosition() const {
    return position;
}

const glm::vec3& Light::getColor() const {
    return color;
}

const glm::vec3 Light::getDirection() const {
    return direction;
}

float Light::getAngle() const {
    return angle;
}

int Light::getType() const {
    return type;
}

void Light::draw() const {
    Transformation transform;

    transform.addTransformation(new Translation(position));
    transform.addTransformation(new Scale(glm::vec3(scale)));

    glm::mat4 modelMatrix = transform.apply(glm::mat4(1.0f));
    lightShader.use();
    lightShader.setUniform("modelMatrix", modelMatrix);
    lightModel.draw();
    lightShader.free();
}


