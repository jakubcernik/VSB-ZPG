#pragma once
#include "Application.h"


class Models
{
public:
    Models();
    ~Models();
    void createModels();
    void drawSquare();
    void drawTriangle();

private:
    GLuint VAO_square;
    GLuint VAO_triangle;
};