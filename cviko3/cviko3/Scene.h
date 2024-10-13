#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "DrawableObject.h"

class Scene {
protected:
    std::vector<DrawableObject> objects;

public:
    void addObject(const DrawableObject& object);
    virtual void render();
};

#endif // SCENE_H
