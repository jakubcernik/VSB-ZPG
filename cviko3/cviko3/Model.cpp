#include "Model.h"
#include "tree.h" // Soubor, kter� obsahuje pole modelu
#include <GL/glew.h>
#include <iostream>

Model::Model() {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    // Na�te data modelu (pole `tree`) p��mo do OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW);
}

Model::~Model() {
    glDeleteBuffers(1, &id);
}

void Model::draw() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);

    // Povolen� atribut�, pokud pou��v� nap��klad pozici a norm�ly
    glEnableVertexAttribArray(0); // P�edpoklad: Atribut pozice je 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1); // P�edpoklad: Atribut norm�l je 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // Vykreslen� modelu
    glDrawArrays(GL_TRIANGLES, 0, 92814); // Po�et vertex� dle koment��e v souboru tree.h

    // Zak�z�n� atribut� po vykreslen�
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
