#pragma once
#include <glm/glm.hpp>

class Transformation {
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

public:
    Transformation();
    glm::mat4 getModelMatrix() const; // Vytvoøí modelovou matici na základì transformací
};
