#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch);

    glm::mat4 getViewMatrix() const;

    void processKeyboard(int direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);

    glm::vec3 getPosition() const;

private:
    void updateCameraVectors();

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
};
