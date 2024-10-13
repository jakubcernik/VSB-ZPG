#include "TreeModel.h"
#include "tree.h" // Soubor s daty modelu
#include <stdlib.h>
#include <iostream>

TreeModel::TreeModel() {
    setupModel();  // Volání setupModel k inicializaci
}

void TreeModel::setupModel() {
    glGenBuffers(1, &id);  // Vytvoøí buffer
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW);
}

void TreeModel::draw() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 92814); // Pokud možno, použij celkový poèet vrcholù

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error in TreeModel::draw(): " << err << std::endl;
    }
}







