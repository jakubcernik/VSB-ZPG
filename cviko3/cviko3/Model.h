#pragma once
#include <string>

class Model {
private:
    unsigned int vao; // Vertex Array Object
    unsigned int vbo; // Vertex Buffer Object

    void loadModel(const std::string& path); // Metoda pro na�ten� modelov�ch dat

public:
    Model(const std::string& path);
    ~Model();

    void draw() const; // Metoda pro vykreslen� modelu

    // Zak�z�n� kop�rov�n�
    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;

    static const unsigned int vertexCount = 92814; // Po�et vrchol�
};
