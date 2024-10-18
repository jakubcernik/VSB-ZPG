#pragma once
#include "VertexShader.h"
#include "FragmentShader.h"
#include <glm/glm.hpp>
#include <string>

class ShaderProgram {
private:
    unsigned int programID;

public:
    ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~ShaderProgram();

    void attachVertexShader(const VertexShader& vertexShader); // For attaching vertex shader
    void attachFragmentShader(const FragmentShader& fragmentShader); // For attaching fragment shader
    void setUniform(const std::string& name, const glm::mat4& matrix);
    void linkProgram();
    void use();
    unsigned int getProgramID() const;
};
