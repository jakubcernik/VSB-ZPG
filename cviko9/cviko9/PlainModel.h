#pragma once

#include "Model.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "plain.h"

class PlainModel : public Model {
private:
    GLuint VAO, VBO;
    const float* getVertexData() const { return plain; }
    unsigned int getVertexCount() const { return 6; }

public:
    PlainModel();
    ~PlainModel();
    void loadModel();
    void draw() const;
};

