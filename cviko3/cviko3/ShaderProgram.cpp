#include "ShaderProgram.h"
#include <GL/glew.h>
#include <iostream>

ShaderProgram::ShaderProgram(const Shader& vertex, const Shader& fragment)
    : vertexShader(vertex), fragmentShader(fragment) {
    programId = glCreateProgram();
    if (programId == 0) {
        std::cerr << "ERROR::SHADER_PROGRAM::CREATE_FAILED\nFailed to create shader program." << std::endl;
        return;
    }

    vertexShader.attachToProgram(programId);
    fragmentShader.attachToProgram(programId);
    linkProgram();

    // Kontrola chyb propojen�
    GLint linkSuccess;
    glGetProgramiv(programId, GL_LINK_STATUS, &linkSuccess);
    if (!linkSuccess) {
        GLchar infoLog[512];
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}


ShaderProgram::~ShaderProgram() {
    glDeleteProgram(programId);
}

void ShaderProgram::linkProgram() {
    glLinkProgram(programId);

    GLint success;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    else {
        std::cout << "Shader program linked successfully. Program ID: " << programId << std::endl;
    }
}





void ShaderProgram::useProgram() const {
    if (programId == 0) {
        std::cerr << "ERROR::SHADER_PROGRAM::INVALID_PROGRAM_ID\nProgram ID is 0. Shader program was not created successfully." << std::endl;
        return;
    }

    glUseProgram(programId);

    GLint activeProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &activeProgram);
    if (activeProgram != programId) {
        std::cerr << "ERROR::SHADER_PROGRAM::USE_FAILED\nProgram ID " << programId << " is not active." << std::endl;
    }
}

unsigned int ShaderProgram::getProgramId() const {
    return programId;
}


void ShaderProgram::setUniformMatrix(const std::string& name, const glm::mat4& matrix) const {
    GLint loc = glGetUniformLocation(programId, name.c_str());
    if (loc == -1) {
        std::cerr << "Warning: Uniform location '" << name << "' not found." << std::endl;
    }
    else {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
    }
}
