#pragma once
#include "Model.h"
#include "bushes.h"

class BushModel : public Model {
public:
    BushModel() { loadModel(); }
    ~BushModel() {}
private:
    const float* getVertexData() const { return bushes; }
    unsigned int getVertexCount() const { return 8730; }
};