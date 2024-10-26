#include "Camera.h"
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch)
    : position(startPosition), worldUp(startUp), yaw(startYaw), pitch(startPitch), movementSpeed(7.5f), mouseSensitivity(0.1f) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(int direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;

    if (direction == 0)
        position += front * velocity;
    if (direction == 1)
        position -= front * velocity;
    if (direction == 2)
        position -= right * velocity;
    if (direction == 3)
        position += right * velocity;

    updateCameraVectors(); // Aktualizace smìru kamery pouze jednou
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVectors(); // Aktualizace smìru kamery pouze jednou
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));

    notify();  // Notifikace o pohybu kamery
}

glm::vec3 Camera::getPosition() const {
    return position;
}

void Camera::addObserver(Observer* observer) {
    observers.push_back(observer);
    notify();
}

void Camera::removeObserver(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Camera::notify() const {
    glm::mat4 view = getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    for (Observer* observer : observers) {
        observer->onNotify(view, projection);
    }
    printf("I notified that camera moved\n");
}
