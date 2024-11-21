#ifndef PLAINMODEL_H
#define PLAINMODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class PlainModel {
public:
    PlainModel();
    ~PlainModel();
    void render();
private:
    GLuint VAO, VBO, EBO;
    void setupModel();
};

#endif // PLAINMODEL_H
