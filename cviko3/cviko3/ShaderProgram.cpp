#include "ShaderProgram.h"
#include <GL/glew.h>
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

void ShaderProgram::use() {
    glUseProgram(programID);
}
