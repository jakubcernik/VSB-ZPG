#pragma once
#include <string>

class Shader {
protected:
    unsigned int shaderID;
    std::string path;

public:
    Shader(const std::string& filePath);
    virtual ~Shader();

    virtual void compileShader() = 0;
    unsigned int getShaderID() const; // Retrieves shader ID
    virtual const char* getShaderType() const = 0;

    // Adding the getID method for consistency with the other code
    unsigned int getID() const { return shaderID; }
};
