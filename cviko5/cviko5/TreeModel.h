#pragma once
#include "Model.h"
#include "tree.h"

class TreeModel : public Model {
protected:
    const float* getVertexData() const override;
    unsigned int getVertexCount() const override;

public:
    TreeModel();
    ~TreeModel();
};