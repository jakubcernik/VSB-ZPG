#pragma once
#include <string>

class Model {
private:
    unsigned int vao;
    unsigned int vbo;

    void loadModel(const std::string& path);

public:
    Model(const std::string& path);
    ~Model();

    void draw() const;

    // Zakázání kopírování kvuli pointerum
    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;

    static const unsigned int vertexCount = 92814;
};
