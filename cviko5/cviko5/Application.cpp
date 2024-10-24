//Application.cpp

#include <GL/glew.h>
#include "Application.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

Application::Application(int width, int height)
    : width(width), height(height), window(nullptr), scene(nullptr),
    camera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f) {
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->inputManager.processMouseMovement(xpos, ypos, app->camera);
}

void Application::initWindow() {
    // Setting OpenGL context v3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Window creation
    window = glfwCreateWindow(width, height, "ZPG CER0548", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create GLFW window!" << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);

    // Mouse callback
    glfwSetCursorPosCallback(window, mouse_callback);

    // Locked cursor into window
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Application::initOpenGL() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    glClearColor(0.63f, 0.81f, 0.82f, 1.0f);

    glDisable(GL_CULL_FACE);  // Turns off culling

}

void Application::setScene(Scene* scenePtr) {
    scene = scenePtr;
}

void Application::run() {
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 1000.0f);


    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        // Inputs
        inputManager.processInput(window, camera, deltaTime);

        // Updating view matrix based on actual camera
        glm::mat4 view = camera.getViewMatrix();


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (scene) {
            scene->render(projection, view, camera.getPosition());
        }

        glfwSwapBuffers(window);

        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << err << std::endl;
        }
    }
}