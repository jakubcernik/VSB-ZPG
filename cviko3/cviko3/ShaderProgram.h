#pragma once
#include "VertexShader.h"
#include "FragmentShader.h"

class ShaderProgram {
private:
    unsigned int programID;
    VertexShader vertexShader;
    FragmentShader fragmentShader;

    void compileAndLinkShaders(); // Intern� metoda pro sestaven� shaderu.

public:
    ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
    void use(); // Aktivuje shader program
};
