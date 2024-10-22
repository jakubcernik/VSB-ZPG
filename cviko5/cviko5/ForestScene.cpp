//ForestScene.cpp

#include "ForestScene.h"
#include "Transformation.h"
#include "Light.h"
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

glm::vec3 generateAutumnColor() {
    static default_random_engine engine{ random_device{}() };
    uniform_real_distribution<float> redDistribution(0.7f, 1.0f);   // Vyšší základ pro èervenou složku (blíže k 1)
    uniform_real_distribution<float> greenDistribution(0.6f, 1.0f); // Vyšší základ pro zelenou složku (blíže k 1)
    uniform_real_distribution<float> blueDistribution(0.0f, 0.2f);  // Nižší hodnota pro modrou složku

    float red = redDistribution(engine);
    float green = greenDistribution(engine);
    float blue = blueDistribution(engine);

    return glm::vec3(red, green, blue);
}




ForestScene::ForestScene(int treeCount)
    : treeModel("tree.h"),
    bushModel("bush.h"),
    treeShaderProgram("tree_vertex_shader.glsl", "tree_fragment_shader.glsl"),
    bushShaderProgram("bush_vertex_shader.glsl", "bush_fragment_shader.glsl") {

    sceneLight = new Light(glm::vec3(50.0f, 10.0f, 10.0f), glm::vec3(1.0f, 0.5f, 0.3f));  // Teplé svìtlo s èerveným/oranžovým nádechem
    sceneLight->addObserver(&treeShaderProgram);  // Shadery budou pozorovat svìtlo
    sceneLight->addObserver(&bushShaderProgram);

    createForest(treeCount);
}

void ForestScene::createForest(int treeCount) {
    srand(static_cast<unsigned>(time(nullptr)));

    float groundLevel = 0.0f;

    for (int i = 0; i < treeCount; ++i) {
        Transformation treeTransform, bushTransform;

        glm::vec3 treeRandomPosition = generateRandomVec3(-100.0f, 100.0f, groundLevel, groundLevel, -100.0f, 100.0f);
        glm::vec3 bushRandomPosition = generateRandomVec3(-100.0f, 100.0f, groundLevel, groundLevel, -100.0f, 100.0f);

        treeTransform.translate(treeRandomPosition);
        bushTransform.translate(bushRandomPosition);

        float randomRotationY = static_cast<float>(std::rand() % 360);
        treeTransform.rotate(0, randomRotationY, 0);
        bushTransform.rotate(0, randomRotationY, 0);

        treeTransform.setScale(glm::vec3(generateRandomFloat(1.5, 3.0)));
        bushTransform.setScale(glm::vec3(generateRandomFloat(15.0, 25.0)));

        glm::vec3 autumnColor = generateAutumnColor();  // Generování podzimní barvy

        // Vytvoøení objektù stromu a keøe s jejich barvami
        DrawableObject tree(treeModel, treeTransform, treeShaderProgram, true, autumnColor);
        DrawableObject bush(bushModel, bushTransform, bushShaderProgram, false, glm::vec3(0.1f, 0.8f, 0.2f));

        addObject(tree);
        addObject(bush);
    }
}


void ForestScene::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {
    glm::vec3 lightPos = sceneLight->getPosition();
    glm::vec3 lightColor = sceneLight->getColor();

    for (const auto& object : objects) {
        if (object.isTree()) {
            treeShaderProgram.use();
            glm::vec3 autumnColor = object.getColor();  // Použít uloženou barvu
            treeShaderProgram.setUniform("objectColor", autumnColor);
            treeShaderProgram.setLightingUniforms(lightPos, viewPos, lightColor, autumnColor);
        }
        else {
            bushShaderProgram.use();
            glm::vec3 bushColor = object.getColor();  // Použít uloženou barvu
            bushShaderProgram.setUniform("objectColor", bushColor);
            bushShaderProgram.setLightingUniforms(lightPos, viewPos, lightColor, bushColor);
        }

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