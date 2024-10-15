#include "ForestScene.h"
#include "DrawableObject.h"
#include "Transformation.h"
#include <glm/glm.hpp>
#include <cstdlib>
#include <ctime>

ForestScene::ForestScene(const std::string& modelPath, const std::string& vertexShaderPath, const std::string& fragmentShaderPath, int treeCount)
    : treeModel(modelPath), shader(vertexShaderPath, fragmentShaderPath) {

    // Vytvoøení lesa
    createForest(treeCount);
}


void ForestScene::createForest(int treeCount) {
    std::srand(std::time(nullptr));

    for (int i = 0; i < treeCount; ++i) {
        Transformation treeTransform;

        glm::vec3 randomPosition = glm::vec3(
            (std::rand() % 200 - 100) * 0.5f,
            0.0f,
            -((std::rand() % 200 + 50) * 0.5f)
        );

        treeTransform.translate(randomPosition);

        float randomRotationY = static_cast<float>(std::rand() % 360);
        treeTransform.rotate(0,randomRotationY,0); // Pouze rotace kolem osy Y

        float randomScaleFactor = 1.5f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 1.0f));
        treeTransform.setScale(glm::vec3(randomScaleFactor));

        DrawableObject tree(treeModel, treeTransform, shader);
        addObject(tree);
    }
}

