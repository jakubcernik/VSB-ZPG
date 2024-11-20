#pragma once

#include "Model.h"
#include "sphere.h"

class SphereModel : public Model {
public:
    SphereModel() { loadModel(); }
    ~SphereModel() {}

private:
    const float* getVertexData() const { return sphere; }

    unsigned int getVertexCount() const { return 2880; }
};