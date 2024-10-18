#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Transformation {
public:
    Transformation();
    void translate(const glm::vec3& deltaPosition);
    void rotate(float angleX, float angleY, float angleZ);
    void setScale(const glm::vec3& newScale);
    glm::mat4 getModelMatrix() const;

private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};
