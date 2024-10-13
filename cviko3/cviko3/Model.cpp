#include "Model.h"
#include <iostream>

Model::Model() {
    glGenBuffers(1, &id);
}

Model::~Model() {
    glDeleteBuffers(1, &id);
}


void Model::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void Model::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint Model::getId() const {
    return id;
}
