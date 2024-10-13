#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include "Scene.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Application {
private:
    std::vector<Scene> scenes;
    int currentScene;
    GLFWwindow* window;

public:
    Application();
    bool initialize();
    void addScene(const Scene& scene);
    void renderScene();
    void pollEvents();
    bool shouldClose() const;
    void terminate();
};

#endif // APPLICATION_H
