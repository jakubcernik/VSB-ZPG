#include "TreeModel.h"

TreeModel::TreeModel() {
    loadModel();
}

TreeModel::~TreeModel() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

const float* TreeModel::getVertexData() const {
    return tree;
}

unsigned int TreeModel::getVertexCount() const {
    return 92814;
}