#include "Shaders.h"
#include "Application.h"

Shaders::Shaders() : shaderProgramRed(0), shaderProgramBlue(0) {}

Shaders::~Shaders() {
    glDeleteProgram(shaderProgramRed);
    glDeleteProgram(shaderProgramBlue);
}

void Shaders::createShaders()
{
    // Vertex shader
    const char* vertex_shader =
        "#version 330\n"
        "layout(location=0) in vec3 vp;"
        "void main () {"
        "     gl_Position = vec4(vp, 1.0);"
        "}";

    // Fragment shader (Red)
    const char* fragment_shader_red =
        "#version 330\n"
        "out vec4 frag_colour;"
        "void main () {"
        "     frag_colour = vec4(1.0, 0.0, 0.0, 1.0);"  // Red color
        "}";

    // Fragment shader (Blue)
    const char* fragment_shader_blue =
        "#version 330\n"
        "out vec4 frag_colour;"
        "void main () {"
        "     frag_colour = vec4(0.0, 0.0, 1.0, 1.0);"  // Blue color
        "}";

    // Compile Shaders
    shaderProgramRed = compileShaderProgram(vertex_shader, fragment_shader_red);
    shaderProgramBlue = compileShaderProgram(vertex_shader, fragment_shader_blue);
}

GLuint Shaders::compileShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_src, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader_src, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void Shaders::useRedProgram()
{
    glUseProgram(shaderProgramRed);
}

void Shaders::useBlueProgram()
{
    glUseProgram(shaderProgramBlue);
}
