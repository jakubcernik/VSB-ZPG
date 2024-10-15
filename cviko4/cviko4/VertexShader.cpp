#include "VertexShader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

// Constructor Implementation
VertexShader::VertexShader(const std::string& filePath) : Shader(filePath) {
    shaderID = glCreateShader(GL_VERTEX_SHADER);
}

VertexShader::~VertexShader() {
    // Base class destructor handles cleanup
}

void VertexShader::compileShader() {
    std::ifstream shaderFile(path);
    std::stringstream shaderStream;

    if (shaderFile.is_open()) {
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
    }
    else {
        std::cerr << "Failed to open vertex shader file: " << path << std::endl;
        return;
    }

    std::string shaderCode = shaderStream.str();
    const char* shaderSource = shaderCode.c_str();
    glShaderSource(shaderID, 1, &shaderSource, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

const char* VertexShader::getShaderType() const {
    return "Vertex Shader";
}
