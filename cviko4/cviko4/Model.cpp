//Model.cpp
#include "Model.h"
#include <GL/glew.h>

Model::~Model() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
