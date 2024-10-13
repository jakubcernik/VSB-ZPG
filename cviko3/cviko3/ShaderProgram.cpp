#include "ShaderProgram.h"
#include <GL/glew.h>
#include <iostream>

ShaderProgram::ShaderProgram(const Shader& vertex, const Shader& fragment)
    : vertexShader(vertex), fragmentShader(fragment) {
    programId = glCreateProgram();
    vertexShader.attachToProgram(programId);
    fragmentShader.attachToProgram(programId);
    linkProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(programId);
}

void ShaderProgram::linkProgram() {
    glLinkProgram(programId);

    int success;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(programId, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void ShaderProgram::useProgram() const {
    glUseProgram(programId);
}

unsigned int ShaderProgram::getProgramId() const {
    return programId;
}
