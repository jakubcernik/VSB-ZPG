#include "ShaderProgram.h"
#include <GL/glew.h>

ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath)
    : vertexShader(vertexPath), fragmentShader(fragmentPath) {
    compileAndLinkShaders();
}

void ShaderProgram::compileAndLinkShaders() {
    // Kompilace a propojení shaderù
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader.getID());
    glAttachShader(programID, fragmentShader.getID());
    glLinkProgram(programID);
    // Kontrola úspìchu propojení
}

void ShaderProgram::use() {
    glUseProgram(programID);
}
