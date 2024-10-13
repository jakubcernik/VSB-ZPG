#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    void setUniformMatrix(const std::string& name, const glm::mat4& matrix) const;
    unsigned int getProgramId() const;
};

#endif // SHADERPROGRAM_H
