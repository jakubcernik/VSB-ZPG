#include "Application.h"
#include <iostream>

Application::Application() : currentScene(0), window(nullptr) {}

bool Application::initialize() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    window = glfwCreateWindow(800, 600, "OpenGL Application", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    return true;
}

void Application::addScene(const Scene& scene) {
    scenes.push_back(scene);
}

void Application::renderScene() {
    if (currentScene < scenes.size()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scenes[currentScene].render();
        glfwSwapBuffers(window);
    }
}

void Application::pollEvents() {
    glfwPollEvents();
}

bool Application::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Application::terminate() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
