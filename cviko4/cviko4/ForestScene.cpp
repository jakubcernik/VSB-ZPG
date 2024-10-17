#include "ForestScene.h"
#include "Transformation.h"
#include <glm/glm.hpp>
#include <cstdlib>
#include <ctime>

ForestScene::ForestScene(int treeCount)
    : treeModel("tree.h"),
    shaderProgram("vertex_shader.glsl", "fragment_shader.glsl") {

    // Vytvoøení lesa
    createForest(treeCount);
}

void ForestScene::createForest(int treeCount) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < treeCount; ++i) {
        Transformation treeTransform;

        glm::vec3 randomPosition = glm::vec3(
            (std::rand() % 200 - 100) * 0.5f,
            (std::rand() % 200 - 100) * 0.5f,
            -((std::rand() % 200 + 50) * 0.5f)
        );

        treeTransform.translate(randomPosition);

        float randomRotationY = static_cast<float>(std::rand() % 360);
        treeTransform.rotate(0, randomRotationY, 0); // Pouze rotace kolem osy Y

        float randomScaleFactor = 1.5f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 1.0f));
        treeTransform.setScale(glm::vec3(randomScaleFactor));

        DrawableObject tree(treeModel, treeTransform, shaderProgram);
        addObject(tree);
    }
}

void ForestScene::render(const glm::mat4& projection) {
    for (const auto& object : objects) {
        object.draw(projection);  // Vykreslení každého objektu
    }
}

void ForestScene::addObject(const DrawableObject& object) {
    objects.push_back(object);  // Pøidejte objekt do vektoru
}
