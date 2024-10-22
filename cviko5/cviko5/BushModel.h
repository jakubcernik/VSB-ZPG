#pragma once
#include "Model.h"

class BushModel : public Model {
public:
    BushModel(const std::string& modelPath);
    ~BushModel();

    void loadModel(const std::string& path) override;
    void draw() const override;

    static const unsigned int vertexCount = 8730;
};
