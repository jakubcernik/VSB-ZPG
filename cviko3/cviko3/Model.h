#pragma once
#include "Application.h"


class Model
{
public:
    Model();
    ~Model();
    void createModel();
    void drawSquare();
    void drawTriangle();

private:
    GLuint VAO_square;
    GLuint VAO_triangle;
};
