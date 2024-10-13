#pragma once
#include "VertexShader.h"
#include "FragmentShader.h"

class ShaderProgram {
private:
    unsigned int programID;
    VertexShader vertexShader;
    FragmentShader fragmentShader;

    void compileAndLinkShaders(); // Interní metoda pro sestavení shaderu.

public:
    ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
    void use(); // Aktivuje shader program
};
