#include "Application.h"
#include "Shaders.h"
#include "Models.h"
#include <stdio.h>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
    fflush(stderr);  // Pro okamžitý výstup do konzole
}

Application::Application()
{
    window = nullptr;
    shaders = new Shaders();
    models = new Models();
}

Application::~Application()
{
    delete shaders;
    delete models;
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initialization()
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(800, 800, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
    glewInit();
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "ERROR: could not initialize GLEW\n");
        exit(EXIT_FAILURE);
    }

    createShaders();
    createModels();
}

void Application::createShaders()
{
    shaders->createShaders();
}

void Application::createModels()
{
    models->createModels();
}

void Application::run()
{
    runStatus();
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Použití èerveného shaderu pro ètverec (dùm)
        shaders->useRedProgram();
        models->drawSquare();

        // Použití modrého shaderu pro trojúhelník (støecha)
        shaders->useBlueProgram();
        models->drawTriangle();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void Application::runStatus()
{
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}
