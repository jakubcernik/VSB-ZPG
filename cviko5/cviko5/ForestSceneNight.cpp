//ForestSceneNight.cpp

#include "ForestSceneNight.h"
#include "Transformation.h"
#include "Light.h"
#include <glm/glm.hpp>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

inline float generateRandomFloat(float min, float max) {
    static default_random_engine engine{ random_device{}() };
    uniform_real_distribution<float> distribution(min, max);
    return distribution(engine);
}

inline glm::vec3 generateRandomVec3(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
    static default_random_engine engine{ random_device{}() };
    uniform_real_distribution<float> distX(minX, maxX);
    uniform_real_distribution<float> distY(minY, maxY);
    uniform_real_distribution<float> distZ(minZ, maxZ);

    return glm::vec3(distX(engine), distY(engine), distZ(engine));
}

inline glm::vec3 generateAutumnColor() {
    static default_random_engine engine{ random_device{}() };
    uniform_real_distribution<float> redDistribution(0.7f, 1.0f);
    uniform_real_distribution<float> greenDistribution(0.6f, 1.0f);
    uniform_real_distribution<float> blueDistribution(0.0f, 0.2f);

    float red = redDistribution(engine);
    float green = greenDistribution(engine);
    float blue = blueDistribution(engine);

    return glm::vec3(red, green, blue);
}

ForestSceneNight::ForestSceneNight(int treeCount)
    : treeModel(),
    bushModel(),
    treeShaderProgram("tree_night_vertex.glsl", "tree_night_fragment.glsl"),
    bushShaderProgram("bush_night_vertex.glsl", "bush_night_fragment.glsl"),
    lightShaderProgram("light_vertex.glsl", "light_fragment.glsl"),
    camera(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f) {

    sceneLight = new Light(glm::vec3(50.0f, 150.0f, 10.0f), glm::vec3(1.0f, 0.5f, 0.3f), lightShaderProgram, 3.0f);
    sceneLight->addObserver(&treeShaderProgram);
    sceneLight->addObserver(&bushShaderProgram);
    camera.addObserver(&treeShaderProgram);
    camera.addObserver(&bushShaderProgram);
    camera.addObserver(&lightShaderProgram);

    createForest(treeCount);

    // Vytvoøení svìtlušek
    for (int i = 0; i < 10; ++i) {
        glm::vec3 fireflyPosition = generateRandomVec3(-100.0f, 100.0f, 0.0f, 20.0f, -100.0f, 100.0f);
        Light* firefly = new Light(fireflyPosition, glm::vec3(1.0f, 1.0f, 0.0f), lightShaderProgram, 0.5f);
        fireflies.push_back(firefly);
    }
}

void ForestSceneNight::createForest(int treeCount) {
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

        glm::vec3 autumnColor = generateAutumnColor();

        DrawableObject tree(treeModel, treeTransform, treeShaderProgram, true, autumnColor);
        DrawableObject bush(bushModel, bushTransform, bushShaderProgram, false, glm::vec3(0.1f, 0.8f, 0.2f));

        addObject(tree);
        addObject(bush);
    }
}

void ForestSceneNight::updateFireflies(float deltaTime) {
    for (auto& firefly : fireflies) {
        glm::vec3 position = firefly->getPosition();
        position += generateRandomVec3(-2.0f, 2.0f, 0.0f, 0.0f, -2.0f, 2.0f) * deltaTime;
        firefly->setPosition(position);
    }
}

void ForestSceneNight::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 lightPos = sceneLight->getPosition();
    glm::vec3 lightColor = sceneLight->getColor();

    glClearColor(0.05f, 0.05f, 0.2f, 1.0f);

    // Update and render fireflies
    updateFireflies(0.016f); // Assuming deltaTime is 16 ms (60 FPS)

    // Pass fireflies to shader
    std::vector<glm::vec3> lightPositions = { lightPos };
    std::vector<glm::vec3> lightColors = { lightColor };

    for (const auto& firefly : fireflies) {
        lightPositions.push_back(firefly->getPosition());
        lightColors.push_back(firefly->getColor());
    }

    for (const auto& object : objects) {
        if (object.isTree()) {
            treeShaderProgram.use();
            glm::vec3 autumnColor = object.getColor();
            treeShaderProgram.setMultipleLightingUniforms(lightPositions, lightColors, viewPos, autumnColor);
        }
        else {
            bushShaderProgram.use();
            glm::vec3 bushColor = object.getColor();
            bushShaderProgram.setMultipleLightingUniforms(lightPositions, lightColors, viewPos, bushColor);
        }

        object.draw();
    }

    for (const auto& firefly : fireflies) {
        firefly->draw();
    }

    sceneLight->draw();
}



Camera& ForestSceneNight::getCamera() {
    return camera;
}

void ForestSceneNight::setCamera(Camera& camera) {
    camera.addObserver(&treeShaderProgram);
    camera.addObserver(&bushShaderProgram);
    camera.addObserver(&lightShaderProgram);
}