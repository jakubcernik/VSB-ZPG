//BushModel.cpp

#include "BushModel.h"
#include <GL/glew.h>
#include <iostream>
#include "bushes.h"
using namespace std;

BushModel::BushModel(const std::string& modelPath) {
    loadModel(modelPath);
}

BushModel::~BushModel() {}

void BushModel::loadModel(const string& path) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    if (vao == 0 || vbo == 0) {
        printf("Error generating OpenGL buffers!");
        return;
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Loading data for positions and normals
    glBufferData(GL_ARRAY_BUFFER, sizeof(bushes), bushes, GL_STATIC_DRAW);

    // Attributes positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Attributes normal
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
