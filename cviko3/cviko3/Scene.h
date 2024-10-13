#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "DrawableObject.h"

class Scene {
protected:
    std::vector<std::shared_ptr<DrawableObject>> objects;

public:
    void addObject(const std::shared_ptr<DrawableObject>& object);
    virtual void render();
};

#endif // SCENE_H
