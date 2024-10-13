#define GLM_ENABLE_EXPERIMENTAL
#include "ForestScene.h"
#include "DrawableObject.h"
#include "Transformation.h"
#include <glm/glm.hpp>
#include <cstdlib>
#include <ctime>


ForestScene::ForestScene(const std::string& modelPath, const std::string& vertexShaderPath, const std::string& fragmentShaderPath, int treeCount) {
    // Inicializace shader programu
    ShaderProgram shader(vertexShaderPath, fragmentShaderPath);

    // Vytvoøení lesa
    createForest(modelPath, shader, treeCount);
}

void ForestScene::createForest(const std::string& modelPath, const ShaderProgram& shader, int treeCount) {
    // Naètení modelu stromu
    Model treeModel(modelPath);

    // Inicializace náhodných èísel
    std::srand(std::time(nullptr));

    // Pøidání náhodnì transformovaných stromù do scény
    for (int i = 0; i < treeCount; ++i) {
        Transformation treeTransform;

        // Nastavení náhodné pozice
        glm::vec3 randomPosition = glm::vec3(
            (std::rand() % 100 - 50) * 0.5f, // x mezi -25 a 25
            0.0f, // y
            (std::rand() % 100 - 50) * 0.5f  // z mezi -25 a 25
        );
        treeTransform.translate(randomPosition);

        // Náhodná rotace kolem osy Y
        float randomRotationY = static_cast<float>(std::rand() % 360);
        treeTransform.rotate(glm::vec3(0.0f, randomRotationY, 0.0f));

        // Náhodné mìøítko mezi 0.8 a 1.2
        float randomScaleFactor = 0.8f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.4f));
        treeTransform.setScale(glm::vec3(randomScaleFactor));

        // Vytvoøení DrawableObjectu stromu
        DrawableObject tree(treeModel, treeTransform, shader);

        // Pøidání stromu do scény
        addObject(tree);
    }
}
