#include "TreeModel.h"
#include <GL/glew.h>
#include <iostream>
#include "tree.h"

TreeModel::TreeModel(const std::string& modelPath) {
    loadModel(modelPath);  // Pøedáme cestu k modelu
}

TreeModel::~TreeModel() {
    // Destruktor se postará o uvolnìní prostøedkù z tøídy `Model`
}

void TreeModel::loadModel(const std::string& path) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    if (vao == 0 || vbo == 0) {
        std::cerr << "Error generating OpenGL buffers!" << std::endl;
        return;
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Specifické naèítání dat do bufferu pro strom
    glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW);

    // Definice atributù
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TreeModel::draw() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}
