#include <GL/glew.h> // Přidej do Application.cpp, pokud ještě není zahrnuto
#include "Application.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;

// Konstruktor nastaví šířku, výšku a inicializuje OpenGL a okno
Application::Application(int width, int height)
    : width(width), height(height), window(nullptr), scene(nullptr) {
    initGLFW();
    initWindow();
    initOpenGL();
}


// Destruktor, uvolnění zdrojů
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

void Application::initWindow() {
    // Nastavení kontextu OpenGL verze 3.3, pro starší verze by bylo nutné nastavit jinak
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Vytvoření okna
    window = glfwCreateWindow(width, height, "OpenGL Application", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create GLFW window!" << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
}

void Application::initOpenGL() {
    // Inicializace GLEW po vytvoření okna a nastavení kontextu
    glewExperimental = GL_TRUE; // Povolení experimentálních funkcí GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);
    // Další nastavení (např. glClearColor) podle potřeby

    // Nastav barvu pozadí
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
}

void Application::setScene(Scene* scenePtr) {
    scene = scenePtr;
}

void Application::run() {
    glm::mat4 projection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, -50.0f, 50.0f);



    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (scene) {
            scene->render(projection);
        }

        glfwSwapBuffers(window);

        // Kontrola chyb OpenGL
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << err << std::endl;
        }
    }
}




