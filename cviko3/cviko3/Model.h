#pragma once
#include <string>

class Model {
private:
    unsigned int modelID;
    void loadModel(const std::string& path);

public:
    Model(const std::string& path);
    void draw() const;
};
