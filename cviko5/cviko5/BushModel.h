#pragma once
#include "Model.h"
#include "bushes.h"

class BushModel : public Model {
protected:
    const float* getVertexData() const override;
    unsigned int getVertexCount() const override;

public:
    BushModel();
    ~BushModel();
};