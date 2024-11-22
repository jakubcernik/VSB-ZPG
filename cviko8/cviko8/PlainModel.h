#pragma once

#include "Model.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "plain.h"

class PlainModel : public Model {
public:
    PlainModel();
    ~PlainModel();
    void draw() const;
private:
    GLuint VAO, VBO;
    void loadModel();
    
    const float* getVertexData() const { return plain; }

    unsigned int getVertexCount() const { return 6; }
};

