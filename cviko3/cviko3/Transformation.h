#pragma once
#include <glm/glm.hpp>

class Transformation {
private:
    glm::vec3 position;
    glm::vec3 rotation; // Rotace ulo�en� jako Eulerovy �hly ve stupn�ch
    glm::vec3 scale;

public:
    Transformation();

    // Metody pro nastaven� jednotliv�ch transformac�
    void translate(const glm::vec3& deltaPosition);
    void rotate(const glm::vec3& deltaRotation);
    void setScale(const glm::vec3& newScale);

    glm::mat4 getModelMatrix() const; // Vytvo�� modelovou matici na z�klad� transformac�

    // Metody pro z�sk�n� aktu�ln�ch transformac�
    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;
};
