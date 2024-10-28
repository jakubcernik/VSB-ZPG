// Light.cpp

#include "Light.h"

Light::Light(const glm::vec3& position, const glm::vec3& color)
    : position(position), color(color) {}

void Light::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
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
