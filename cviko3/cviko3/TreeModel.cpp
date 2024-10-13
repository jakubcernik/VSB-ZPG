#include "TreeModel.h"
#include "tree.h" // Soubor s daty modelu

TreeModel::TreeModel() {
    setupModel();
}

void TreeModel::setupModel() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW);
}

void TreeModel::draw() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);

    glEnableVertexAttribArray(0); // Atribut pro pozici
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1); // Atribut pro normály
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glDrawArrays(GL_TRIANGLES, 0, 92814); // Poèet vrcholù dle komentáøe v tree.h

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
