#pragma once

#include "Model.h"
#include "sphere.h"

class SphereModel : public Model {

private:
    const float* getVertexData() const {
        return sphere;
    }

    unsigned int getVertexCount() const {
        return 2880;
    }

public:
    SphereModel() {
        loadModel();
    }

    ~SphereModel() {}
};