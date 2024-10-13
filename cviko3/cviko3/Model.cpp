#include "Model.h"
#include "tree.h" // zahrneme přímo tree.h
#include <GL/glew.h>
#include <iostream>

Model::Model(const std::string& path) {
    loadModel(path);
}

void Model::loadModel(const std::string& path) {
    vao = 0;
    vbo = 0;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    if (vao == 0 || vbo == 0) {
        std::cerr << "Error generating OpenGL buffers!" << std::endl;
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Naplnění dat bufferu přímo pomocí pole `tree`
    glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Error after glBufferData: " << error << std::endl;
    }
    // Specifikace vertex atributů pouze pro pozici (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Odpoutání bufferu a vertex array objektu
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


Model::~Model() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Model::draw() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 92814); // Použijeme pevný počet vrcholů
    glBindVertexArray(0);
}
