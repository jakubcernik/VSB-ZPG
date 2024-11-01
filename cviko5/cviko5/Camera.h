#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Observer.h"
#include "Observable.h"
#include <vector>

class Camera : public Observable {
public:
    Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch);
    
    glm::vec3 getPosition() const;
    glm::mat4 getViewMatrix() const;

    void processKeyboard(int direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);

    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);

private:
    void updateCameraVectors();
    void notify() const;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;

    std::vector<Observer*> observers;
};
