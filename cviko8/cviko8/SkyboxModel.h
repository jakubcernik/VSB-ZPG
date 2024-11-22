#pragma once

#include "Model.h"
#include "skycube.h"

class SkyboxModel : public Model {
public:
    SkyboxModel();
    ~SkyboxModel();
    void draw() const;

private:
    GLuint VAO, VBO;
    const float* getVertexData() const { return skycube; }

    unsigned int getVertexCount() const { return 108; }
    void loadModel();
};