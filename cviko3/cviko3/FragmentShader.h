#pragma once
#include <string>

class FragmentShader {
private:
    unsigned int shaderID;
    void compile(const std::string& source);

public:
    FragmentShader(const std::string& filePath);
    unsigned int getID() const;
};
