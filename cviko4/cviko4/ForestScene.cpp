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
            (std::rand() % 200 - 100) * 0.5f,  // x mezi -50 a 50
            (std::rand() % 200 - 100) * 0.5f,
            (std::rand() % 200 - 100) * 0.5f
        );

        treeTransform.translate(randomPosition);

        float randomRotationY = static_cast<float>(std::rand() % 360);
        treeTransform.rotate(glm::vec3(0.0f, randomRotationY, 0.0f));

        float randomScaleFactor = 1.5f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 1.5f));
        treeTransform.setScale(glm::vec3(randomScaleFactor));

        // Použití trvalých instancí shaderu a modelu
        DrawableObject tree(treeModel, treeTransform, shader);
        addObject(tree);
    }
}
