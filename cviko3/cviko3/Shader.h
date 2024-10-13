#pragma once
#include "Application.h"

class Shader
{
public:
    Shader();
    ~Shader();
    void createShader();
    void useRedProgram();
    void useBlueProgram();
private:
    GLuint shaderProgramRed;
    GLuint shaderProgramBlue;
    GLuint compileShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src);
};
