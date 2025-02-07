#pragma once

#include "Scene.h"
#include <GLFW/glfw3.h>

class Camera;

class InputManager {
public:
    InputManager();

    void processInput(GLFWwindow* window, Camera& camera, float deltaTime);
    void processMouseMovement(double xpos, double ypos, Camera& camera);
    void setLockedStatus(bool status);
    bool getLockedStatus() const;
    void resetMousePosition();

private:
    bool firstMouse;
    float lastX;
    float lastY;
    bool lockedStatus;
};
