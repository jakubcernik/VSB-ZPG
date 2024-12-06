#pragma once

#include "Model.h"
#include "tree.h"

class TreeModel : public Model {
public:
    TreeModel() { loadModel(); }
    ~TreeModel() {}

private:
    const float* getVertexData() const override { return tree; }
    unsigned int getVertexCount() const override { return 92814; }
};