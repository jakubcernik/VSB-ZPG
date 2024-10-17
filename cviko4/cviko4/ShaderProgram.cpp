#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    programID = glCreateProgram();

    // Create shader objects
    VertexShader vertexShader(vertexShaderPath);
    FragmentShader fragmentShader(fragmentShaderPath);

    // Compile shaders
    vertexShader.compileShader();
    fragmentShader.compileShader();

    // Attach and link
    attachVertexShader(vertexShader);
    attachFragmentShader(fragmentShader);
    linkProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(programID);
}

void ShaderProgram::attachVertexShader(const VertexShader& vertexShader) {
    glAttachShader(programID, vertexShader.getID()); // Attaching the vertex shader
}

void ShaderProgram::attachFragmentShader(const FragmentShader& fragmentShader) {
    glAttachShader(programID, fragmentShader.getID()); // Attaching the fragment shader
}

void ShaderProgram::linkProgram() {
    glLinkProgram(programID);

    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void ShaderProgram::use() {
    glUseProgram(programID); // Setting the program as active
}

unsigned int ShaderProgram::getProgramID() const {
    return programID;
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}