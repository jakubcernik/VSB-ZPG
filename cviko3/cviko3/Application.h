#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <stdio.h>

// Předběžné deklarace
class Shader;
class Model;

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void window_focus_callback(GLFWwindow* window, int focused);
static void window_iconify_callback(GLFWwindow* window, int iconified);
static void window_size_callback(GLFWwindow* window, int width, int height);
static void cursor_callback(GLFWwindow* window, double x, double y);
static void button_callback(GLFWwindow* window, int button, int action, int mode);

class Application
{
public:
    Application();
    ~Application();
    void initialization();
    void run();
    void createShaders();
    void createModels();
    void runStatus();

private:
    GLFWwindow* window;
    Shader* shaders;
    Model* models;
};
