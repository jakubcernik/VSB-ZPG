#pragma once
#include <vector>
#include "DrawableObject.h"

class Scene {
private:
    std::vector<DrawableObject> objects;

public:
    void addObject(const DrawableObject& object);
    void render(); // Vykresl� v�echny objekty ve sc�n�.
};
