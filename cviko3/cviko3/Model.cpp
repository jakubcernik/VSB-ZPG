#include "Model.h"
#include "tree.h" // Soubor, který obsahuje pole modelu
#include <GL/glew.h>
#include <iostream>

Model::Model() {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    // Naète data modelu (pole `tree`) pøímo do OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW);
}

Model::~Model() {
    glDeleteBuffers(1, &id);
}

void Model::draw() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);

    // Povolení atributù, pokud používáš napøíklad pozici a normály
    glEnableVertexAttribArray(0); // Pøedpoklad: Atribut pozice je 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1); // Pøedpoklad: Atribut normál je 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // Vykreslení modelu
    glDrawArrays(GL_TRIANGLES, 0, 92814); // Poèet vertexù dle komentáøe v souboru tree.h

    // Zakázání atributù po vykreslení
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
