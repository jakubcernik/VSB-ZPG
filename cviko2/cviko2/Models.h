#pragma once
#include "Application.h"


class Models
{
public:
    Models();
    ~Models();
    void createModels();
    void draw();

private:
    GLuint VAO;
};
