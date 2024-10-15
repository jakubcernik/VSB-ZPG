#pragma once
#include <string>

class VertexShader 
{

public:
    VertexShader(const std::string& filePath);
    unsigned int getID() const;

private:
    unsigned int shaderID;
    void compile(const std::string& source);

};
