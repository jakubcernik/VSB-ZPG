#pragma once
#include <glm/glm.hpp>

class Transformation {
private:
    glm::vec3 position;
    glm::vec3 rotation; // Rotace uložená jako Eulerovy úhly ve stupních
    glm::vec3 scale;

public:
    Transformation();

    // Metody pro nastavení jednotlivých transformací
    void translate(const glm::vec3& deltaPosition);
    void rotate(const glm::vec3& deltaRotation);
    void setScale(const glm::vec3& newScale);

    glm::mat4 getModelMatrix() const; // Vytvoøí modelovou matici na základì transformací

    // Metody pro získání aktuálních transformací
    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;
};
