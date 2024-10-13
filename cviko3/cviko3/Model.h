#pragma once
#include <string>

class Model {
private:
    unsigned int vao; // Vertex Array Object
    unsigned int vbo; // Vertex Buffer Object

    void loadModel(const std::string& path); // Metoda pro naètení modelových dat

public:
    Model(const std::string& path);
    ~Model();

    void draw() const; // Metoda pro vykreslení modelu

    // Zakázání kopírování
    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;

    static const unsigned int vertexCount = 92814; // Poèet vrcholù
};
