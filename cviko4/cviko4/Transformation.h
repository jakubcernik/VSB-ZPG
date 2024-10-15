#pragma once
#include <glm/glm.hpp>

class Transformation {
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

public:
    Transformation();

    // Metody pro nastavení jednotlivých transformací
    void translate(const glm::vec3& deltaPosition);
    void rotate(const glm::vec3& deltaRotation);
    void setScale(const glm::vec3& newScale);

    glm::mat4 getModelMatrix() const; // Celkova matice
};
