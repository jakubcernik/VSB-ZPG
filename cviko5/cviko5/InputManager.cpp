//InputManager.cpp

#include "InputManager.h"
#include "Camera.h"

InputManager::InputManager() : firstMouse(true), lastX(400), lastY(300) {}

void InputManager::processInput(GLFWwindow* window, Camera& activeCamera, float deltaTime) {
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            activeCamera.processKeyboard(0, deltaTime);
            printf("W\n");
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            activeCamera.processKeyboard(1, deltaTime);
            printf("S\n");
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            activeCamera.processKeyboard(2, deltaTime);
            printf("A\n");
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            activeCamera.processKeyboard(3, deltaTime);
            printf("D\n");
        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            activeCamera.processKeyboard(4, deltaTime);
            printf("Shift\n");
        }
    }
}

void InputManager::processMouseMovement(double xpos, double ypos, Camera& camera) {
    if (firstMouse) {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos - lastX);
    float yoffset = static_cast<float>(lastY - ypos); // Y axis is reversed
    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    camera.processMouseMovement(xoffset, yoffset);
}

void InputManager::setLockedStatus(bool status) {
    lockedStatus = status;
}

bool InputManager::getLockedStatus() const {
    return lockedStatus;
}

void InputManager::resetMousePosition() {
    firstMouse = true;
}
