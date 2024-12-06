#pragma once

#include "Model.h"
#include "sphere.h"

class SphereModel : public Model {
public:
    SphereModel() { loadModel(); }
    ~SphereModel() {}

private:
    const float* getVertexData() const override { return sphere; }
    unsigned int getVertexCount() const override { return 2880; }
};