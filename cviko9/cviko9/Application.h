﻿#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "Scene.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include "InputManager.h"

class Application {
private:
    GLFWwindow* window;
    Scene* activeScene;
    int width;
    int height;
    bool lockedStatus;

    void initGLFW();
    void initWindow();
    void initOpenGL();
    

public:
    Application(int width, int height);
    ~Application();
    Scene* getActiveScene() const { return activeScene; }
    void run(Scene& triangleScene, Scene& forestScene, Scene& sphereScene, Scene& shaderShowcaseScene, Scene& forestSceneNight, Scene& materialScene);
    void setScene(Scene* scenePtr);
    InputManager inputManager;
};
