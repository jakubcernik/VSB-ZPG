#pragma once

#include "Scene.h"
#include <GLFW/glfw3.h>

class Camera;

class InputManager {
public:
    InputManager();

    void processInput(GLFWwindow* window, Camera& camera, float deltaTime, Scene*& activeScene, Scene& forestScene, Scene& sphereScene);
    void processMouseMovement(double xpos, double ypos, Camera& camera);

private:
    bool firstMouse;
    float lastX;
    float lastY;
};
