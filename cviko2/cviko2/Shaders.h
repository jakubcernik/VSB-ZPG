#pragma once
#include "Application.h"

class Shaders
{
public:
    Shaders();
    ~Shaders();
    void createShaders();
    void useProgram();
    GLuint getProgram() const;
private:
    GLuint shaderProgram;
};
