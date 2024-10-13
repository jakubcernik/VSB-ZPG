#include "Shader.h"
#include <GL/glew.h>
#include <iostream>

Shader::Shader(const std::string& source, unsigned int type)
    : shaderType(type) {
    compileShader(source);
}

Shader::~Shader() {
    glDeleteShader(id);
}

void Shader::compileShader(const std::string& source) {
    const char* sourceCStr = source.c_str();
    id = glCreateShader(shaderType);
    glShaderSource(id, 1, &sourceCStr, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

unsigned int Shader::getId() const {
    return id;
}

void Shader::attachToProgram(unsigned int programId) const {
    glAttachShader(programId, id);
}
