#include "FragmentShader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
using namespace std;

FragmentShader::FragmentShader(const string& filePath) {
    ifstream shaderFile(filePath);
    stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    string code = shaderStream.str();
    compile(code);
}

void FragmentShader::compile(const string& source) {
    shaderID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);
    // Kontrola úspìchu kompilace
}

unsigned int FragmentShader::getID() const {
    return shaderID;
}
