// Light.h
#pragma once
#include "Observable.h"
#include <glm/glm.hpp>

class Light : public Observable {
public:
    Light(const glm::vec3& position, const glm::vec3& color);
    void setPosition(const glm::vec3& newPosition);
    void setColor(const glm::vec3& newColor);

    const glm::vec3& getPosition() const;
    const glm::vec3& getColor() const;

private:
    glm::vec3 position;
    glm::vec3 color;
};
