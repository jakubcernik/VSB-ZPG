#include "Shader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& filePath, unsigned int type)
    : shaderType(type) {
    std::string shaderSource = loadShaderSource(filePath);
    if (shaderSource.empty()) {
        std::cerr << "ERROR::SHADER::EMPTY_SOURCE\nShader source is empty for file: " << filePath << std::endl;
        return;
    }
    compileShader(shaderSource);
}

Shader::~Shader() {
    glDeleteShader(id);
}

std::string Shader::loadShaderSource(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        std::cerr << "ERROR::SHADER::FILE_NOT_FOUND\nCould not open shader file: " << filePath << std::endl;
        return "";
    }
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    return shaderStream.str();
}

void Shader::compileShader(const std::string& source) {
    id = glCreateShader(shaderType);
    const char* sourceCStr = source.c_str();
    glShaderSource(id, 1, &sourceCStr, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else {
        std::cout << "Shader compiled successfully." << std::endl;
    }
}


unsigned int Shader::getId() const {
    return id;
}

void Shader::attachToProgram(unsigned int programId) const {
    glAttachShader(programId, id);

    // Kontrola zda bylo pøipojení úspìšné
    GLint attached;
    glGetProgramiv(programId, GL_ATTACHED_SHADERS, &attached);
    if (attached <= 0) {
        std::cerr << "ERROR::SHADER::ATTACHMENT_FAILED\nShader ID " << id << " could not be attached to Program ID " << programId << std::endl;
    }
}

