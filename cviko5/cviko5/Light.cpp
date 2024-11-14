// Light.cpp

#include "Light.h"
#include "Transformation.h"
#include "Translation.h"
#include "Scale.h"

Light::Light(const glm::vec3& position, const glm::vec3& color, ShaderProgram& lightShader, float scale)
    : position(position), color(color), lightShader(lightShader), scale(scale) {}

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

void Light::draw() const {
    std::shared_ptr<Transformation> transform = std::make_shared<Transformation>();
    transform->addTransformation(std::make_shared<Translation>(position));
    transform->addTransformation(std::make_shared<Scale>(glm::vec3(scale)));

    glm::mat4 modelMatrix = transform->apply(glm::mat4(1.0f));
    lightShader.use();
    lightShader.setUniform("modelMatrix", modelMatrix);
    lightModel.draw();
    lightShader.free();
}

