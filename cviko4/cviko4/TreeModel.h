#pragma once
#include "Model.h"

class TreeModel : public Model {
public:
    TreeModel(const std::string& modelPath);
    ~TreeModel();

    void loadModel(const std::string& path) override;
    void draw() const override;
};
