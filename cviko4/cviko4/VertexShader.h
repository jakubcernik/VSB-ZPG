#pragma once
#include <string>

class VertexShader {
private:
    unsigned int shaderID;
    void compile(const std::string& source);

public:
    VertexShader(const std::string& filePath);
    unsigned int getID() const;
};
