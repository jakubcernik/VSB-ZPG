#ifndef FOREST_SCENE_H
#define FOREST_SCENE_H

#include "Scene.h"

class ForestScene : public Scene {
private:
    std::vector<std::shared_ptr<DrawableObject>> objects;
public:
    ForestScene();
    void setupScene();
    void render() override;
};

#endif // FOREST_SCENE_H
