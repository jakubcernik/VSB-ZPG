#include "ForestScene.h"
#include "Transformation.h"
#include <glm/glm.hpp>
#include <cstdlib>
#include <ctime>
#include <random>

float generateRandomFloat(float min, float max) {
    static std::default_random_engine engine{ std::random_device{}() };
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(engine);
}

ForestScene::ForestScene(int treeCount)
    : treeModel("tree.h"),
    bushModel("bush.h"),
    treeShaderProgram("tree_vertex_shader.glsl", "tree_fragment_shader.glsl"),
    bushShaderProgram("bush_vertex_shader.glsl", "bush_fragment_shader.glsl")
{

    // Vytvoøení lesa
    createForest(treeCount);
}

void ForestScene::createForest(int treeCount) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < treeCount; ++i) {
        Transformation treeTransform, bushTransform;

        glm::vec3 treeRandomPosition = glm::vec3(
            (std::rand() % 200 - 100) * 0.5f,
            (std::rand() % 200 - 100) * 0.5f,
            -((std::rand() % 200 + 50) * 0.5f)
        );

        glm::vec3 bushRandomPosition = glm::vec3(
            (std::rand() % 200 - 100) * 0.5f,
            (std::rand() % 200 - 100) * 0.5f,
            -((std::rand() % 200 + 50) * 0.5f)
        );

        treeTransform.translate(treeRandomPosition);
        bushTransform.translate(bushRandomPosition);

        float randomRotationY = static_cast<float>(std::rand() % 360);
        treeTransform.rotate(0, randomRotationY, 0); // Pouze rotace kolem osy Y
        bushTransform.rotate(0, randomRotationY, 0);

        treeTransform.setScale(glm::vec3(generateRandomFloat(1.5,3.0)));
        bushTransform.setScale(glm::vec3(generateRandomFloat(15.0, 25.0)));

        DrawableObject tree(treeModel, treeTransform, treeShaderProgram);
        DrawableObject bush(bushModel, bushTransform, bushShaderProgram);
        addObject(tree);
        addObject(bush);
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
