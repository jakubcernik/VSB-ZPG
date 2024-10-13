#ifndef FOREST_SCENE_H
#define FOREST_SCENE_H

#include "Scene.h"

class ForestScene : public Scene {
public:
    ForestScene();
    void setupScene();
    void render() override;
};

#endif // FOREST_SCENE_H
