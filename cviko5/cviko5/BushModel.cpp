#include "BushModel.h"

BushModel::BushModel() {
    loadModel();
}

BushModel::~BushModel() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

const float* BushModel::getVertexData() const {
    return bushes;
}

unsigned int BushModel::getVertexCount() const {
    return 8730;
}