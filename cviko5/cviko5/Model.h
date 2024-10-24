#pragma once
#include <string>
#include <GL/glew.h>

class Model {
protected:
    unsigned int vao;
    unsigned int vbo;

    virtual const float* getVertexData() const = 0;
    virtual unsigned int getVertexCount() const = 0;

    void loadModel();

public:
    Model();
    virtual ~Model();

    virtual void draw() const;
};
