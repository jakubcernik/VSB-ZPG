#pragma once
#include "VertexShader.h"
#include "FragmentShader.h"
#include <glm/glm.hpp>


class ShaderProgram {
private:
    unsigned int programID;
    VertexShader vertexShader;
    FragmentShader fragmentShader;

    void compileAndLinkShaders();

public:
    ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void use() const;
    void setUniform(const std::string& name, const glm::mat4& matrix) const;
};
