#pragma once
#include <GL/glew.h>
#include <string>


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
