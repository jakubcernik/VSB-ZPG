#include <GL/glew.h>
#include "Application.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

Application::Application(int width, int height)
    : width(width), height(height), window(nullptr), activeScene(nullptr), lockedStatus(true){
    initGLFW();
    initWindow();
    initOpenGL();
}

Application::~Application() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initGLFW() {
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW!" << endl;
        exit(EXIT_FAILURE);
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            app->inputManager.setLockedStatus(true);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            app->inputManager.resetMousePosition();
        }
        else if (action == GLFW_RELEASE) {
            app->inputManager.setLockedStatus(false);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            app->inputManager.resetMousePosition();
        }
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app->inputManager.getLockedStatus() && app->getActiveScene()) {
        Camera& activeCamera = app->getActiveScene()->getCamera();
        app->inputManager.processMouseMovement(xpos, ypos, activeCamera);
    }
}


void Application::initWindow() {
    window = glfwCreateWindow(width, height, "ZPG CER0548", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create GLFW window!" << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void Application::initOpenGL() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW!" << endl;
        exit(EXIT_FAILURE);
    }

    // Check the OpenGL version to ensure the context is properly initialized
    const GLubyte* version = glGetString(GL_VERSION);
    if (version) {
        cout << "OpenGL version: " << version << endl;
    }
    else {
        cerr << "Failed to initialize OpenGL context" << endl;
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0f);

    glDisable(GL_CULL_FACE);
}


void Application::setScene(Scene* scenePtr) {
    activeScene = scenePtr;
}


void Application::run(Scene& triangleScene, Scene& forestScene, Scene& sphereScene, Scene& shaderShowcaseScene, Scene& forestSceneNight, Scene& materialScene) {
    bool isTabPressed = false;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 1000.0f);

    activeScene = &triangleScene;  // Default is triangle scene

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        // Scene switching with keys 1, 2, and 3
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            activeScene = &forestScene;
            glfwSetWindowTitle(window, "Forest Scene");
        }
        else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            activeScene = &sphereScene;
            glfwSetWindowTitle(window, "Spheres with light");
        }
        else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            activeScene = &shaderShowcaseScene;
            glfwSetWindowTitle(window, "Shader Showcase Scene");
        }
        else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
            activeScene = &forestSceneNight;
            glfwSetWindowTitle(window, "Forest Scene at night");
        }
		else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
			activeScene = &materialScene;
			glfwSetWindowTitle(window, "Material Showcase Scene");
		}

        Camera& activeCamera = activeScene->getCamera();
        inputManager.processInput(window, activeCamera, deltaTime);

        // Get the view matrix from the active camera
        glm::mat4 view = activeCamera.getViewMatrix();

        // Render the active scene
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        activeScene->render(projection, view, activeCamera.getPosition());

        glfwSwapBuffers(window);
    }
}






