#pragma once
#include <string>

class Model {
protected:
    unsigned int vao;
    unsigned int vbo;

    virtual void loadModel(const std::string& path) = 0;

public:
    Model() : vao(0), vbo(0) {}
    virtual ~Model();
    virtual void draw() const = 0;

    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;

    static const unsigned int vertexCount;
};
