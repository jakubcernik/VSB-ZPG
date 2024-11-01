#pragma once

#include "Model.h"
#include "tree.h"

class TreeModel : public Model {

private:
    const float* getVertexData() const {
        return tree;
    }

    unsigned int getVertexCount() const {
        return 92814;
    }

public:
    TreeModel() {
        loadModel();
    }

    ~TreeModel() {}
};