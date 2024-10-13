#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "Model.h"

class TreeModel : public Model {
private:
    void setupModel() override;

public:
    TreeModel();  // Konstruktor
    void draw() const override;
};

#endif // TREEMODEL_H
