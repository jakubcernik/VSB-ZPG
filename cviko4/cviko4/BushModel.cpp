#include "BushModel.h"
#include <GL/glew.h>
#include <iostream>
#include "bushes.h"

BushModel::BushModel(const std::string& modelPath) {
    loadModel(modelPath);  // P�ed�me cestu k modelu
}

BushModel::~BushModel() {
    // Destruktor se postar� o uvoln�n� prost�edk� z t��dy `Model`
}

void BushModel::loadModel(const std::string& path) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    if (vao == 0 || vbo == 0) {
        std::cerr << "Error generating OpenGL buffers!" << std::endl;
        return;
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Specifick� na��t�n� dat do bufferu pro strom
    glBufferData(GL_ARRAY_BUFFER, sizeof(bushes), bushes, GL_STATIC_DRAW);

    // Definice atribut�
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void BushModel::draw() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}
