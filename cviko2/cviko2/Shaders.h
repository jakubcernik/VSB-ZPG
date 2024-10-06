#pragma once
#include "Application.h"

class Shaders
{
public:
    Shaders();
    ~Shaders();
    void createShaders();
    void useRedProgram();
    void useBlueProgram();
private:
    GLuint shaderProgramRed;
    GLuint shaderProgramBlue;
    GLuint compileShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src);
};
