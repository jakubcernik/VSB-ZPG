//ForestScene.cpp

#include "ForestScene.h"
#include "Transformation.h"
#include <glm/glm.hpp>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

float generateRandomFloat(float min, float max) {
    static default_random_engine engine{random_device{}() };
    uniform_real_distribution<float> distribution(min, max);
    return distribution(engine);
}

glm::vec3 generateRandomVec3(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
    static default_random_engine engine{random_device{}() };
    uniform_real_distribution<float> distX(minX, maxX);
    uniform_real_distribution<float> distY(minY, maxY);
    uniform_real_distribution<float> distZ(minZ, maxZ);

    return glm::vec3(distX(engine), distY(engine), distZ(engine));
}


ForestScene::ForestScene(int treeCount)
    : 
    treeModel("tree.h"),
    bushModel("bush.h"),
    treeShaderProgram("tree_vertex_shader.glsl", "tree_fragment_shader.glsl"),
    bushShaderProgram("bush_vertex_shader.glsl", "bush_fragment_shader.glsl")
{

    createForest(treeCount);
}

void ForestScene::createForest(int treeCount) {
    srand(static_cast<unsigned>(time(nullptr)));

    float groundLevel = 0.0f;  // Height for trees and bushes

    for (int i = 0; i < treeCount; ++i) {
        Transformation treeTransform, bushTransform;

        glm::vec3 treeRandomPosition = generateRandomVec3(-100.0f, 100.0f, groundLevel, groundLevel, -100.0f, 100.0f);
        glm::vec3 bushRandomPosition = generateRandomVec3(-100.0f, 100.0f, groundLevel, groundLevel, -100.0f, 100.0f);

        treeTransform.translate(treeRandomPosition);
        bushTransform.translate(bushRandomPosition);

        // Random rotation only around Y axis
        float randomRotationY = static_cast<float>(std::rand() % 360);
        treeTransform.rotate(0, randomRotationY, 0);
        bushTransform.rotate(0, randomRotationY, 0);

        treeTransform.setScale(glm::vec3(generateRandomFloat(1.5, 3.0)));
        bushTransform.setScale(glm::vec3(generateRandomFloat(15.0, 25.0)));

        // Creating objects and adding them into scene
        DrawableObject tree(treeModel, treeTransform, treeShaderProgram);
        DrawableObject bush(bushModel, bushTransform, bushShaderProgram);
        addObject(tree);
        addObject(bush);
    }
}


void ForestScene::render(const glm::mat4& projection, const glm::mat4& view) {
    for (const auto& object : objects) {
        object.draw(projection, view);
    }
}

void ForestScene::addObject(const DrawableObject& object) {
    objects.push_back(object);
}

void ForestScene::setCamera(Camera& camera) {
    camera.addObserver(&treeShaderProgram);
    camera.addObserver(&bushShaderProgram);
}