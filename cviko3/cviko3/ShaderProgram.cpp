#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

ShaderProgram::ShaderProgram(const string& vertexPath, const string& fragmentPath)
    : vertexShader(vertexPath), fragmentShader(fragmentPath) {
    compileAndLinkShaders();
}

void ShaderProgram::compileAndLinkShaders() {
    // Kompilace a propojen� shader�
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader.getID());
    glAttachShader(programID, fragmentShader.getID());
    glLinkProgram(programID);
    // Kontrola �sp�chu propojen�
}

void ShaderProgram::use() const {
    glUseProgram(programID);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix) const {
    GLuint loc = glGetUniformLocation(programID, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}