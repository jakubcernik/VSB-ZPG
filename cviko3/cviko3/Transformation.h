#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformation {
private:
    glm::mat4 translationMatrix;  // Matice pro posun
    glm::mat4 scaleMatrix;        // Matice pro zmìnu mìøítka
    glm::mat4 rotationMatrix;     // Matice pro rotaci

public:
    Transformation();

    void translate(float x, float y, float z);
    void scale(float sx, float sy, float sz);
    void rotate(float angle, float x, float y, float z);

    glm::mat4 getMatrix() const; // Získání výsledné transformaèní matice
};

#endif // TRANSFORMATION_H
