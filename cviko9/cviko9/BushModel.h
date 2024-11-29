#pragma once
#include "Model.h"
#include "bushes.h"

class BushModel : public Model {
protected:
    const float* getVertexData() const {
        return bushes;
    }

    unsigned int getVertexCount() const {
        return 8730;
    }

public:
    BushModel() {
        loadModel();
    }

    ~BushModel() {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }
};