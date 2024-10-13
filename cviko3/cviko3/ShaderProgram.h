#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Shader.h"

class ShaderProgram {
private:
    unsigned int programId;
    Shader vertexShader;
    Shader fragmentShader;
    void linkProgram();

public:
    ShaderProgram(const Shader& vertex, const Shader& fragment);
    ~ShaderProgram();
    void useProgram() const;
    unsigned int getProgramId() const;
};

#endif // SHADERPROGRAM_H
