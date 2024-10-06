#include "Shaders.h"
#include "Application.h"

Shaders::Shaders() : shaderProgram(0) {}

Shaders::~Shaders() {}

void Shaders::createShaders()
{
    const char* vertex_shader =
        "#version 330\n"
        "layout(location=0) in vec3 vp;"
        "void main () {"
        "     gl_Position = vec4(vp, 1.0);"
        "}";

    const char* fragment_shader =
        "#version 330\n"
        "out vec4 frag_colour;"
        "void main () {"
        "     frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
        "}";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
}

void Shaders::useProgram()
{
    glUseProgram(shaderProgram);
}

GLuint Shaders::getProgram() const
{
    return shaderProgram;
}
