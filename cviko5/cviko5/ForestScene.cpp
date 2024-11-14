// ForestScene.cpp

#include "ForestScene.h"
#include "Transformation.h"
#include "Translation.h"
#include "Rotation.h"
#include "Scale.h"
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

ForestScene::ForestScene(int treeCount)
    : treeModel(),
    bushModel(),
    treeShaderProgram("tree_vertex_shader.glsl", "tree_fragment_shader.glsl"),
    bushShaderProgram("bush_vertex_shader.glsl", "bush_fragment_shader.glsl"),
    lightShaderProgram("light_vertex.glsl", "light_fragment.glsl"),
    //Camera(startPosition, startUp, startYaw, startPitch);
    camera(glm::vec3(0.0f, 50.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -45.0f) {

    sceneLight = new Light(glm::vec3(50.0f, 10.0f, 10.0f), glm::vec3(1.0f, 0.5f, 0.3f), lightShaderProgram);
    sceneLight->addObserver(&treeShaderProgram);
    sceneLight->addObserver(&bushShaderProgram);
    camera.addObserver(&treeShaderProgram);
    camera.addObserver(&bushShaderProgram);
    camera.addObserver(&lightShaderProgram);

    createForest(treeCount);
}

void ForestScene::createForest(int treeCount) {
    srand(static_cast<unsigned>(time(nullptr)));

    float groundLevel = 0.0f;

    for (int i = 0; i < treeCount; ++i) {
        std::shared_ptr<Transformation> treeTransform = std::make_shared<Transformation>();
        std::shared_ptr<Transformation> bushTransform = std::make_shared<Transformation>();

        glm::vec3 treeRandomPosition = generateRandomVec3(-100.0f, 100.0f, groundLevel, groundLevel, -100.0f, 100.0f);
        glm::vec3 bushRandomPosition = generateRandomVec3(-100.0f, 100.0f, groundLevel, groundLevel, -100.0f, 100.0f);

        treeTransform->addTransformation(std::make_shared<Translation>(treeRandomPosition));
        bushTransform->addTransformation(std::make_shared<Translation>(bushRandomPosition));

        float randomRotationY = static_cast<float>(std::rand() % 360);
        treeTransform->addTransformation(std::make_shared<Rotation>(0, randomRotationY, 0));
        bushTransform->addTransformation(std::make_shared<Rotation>(0, randomRotationY, 0));

        treeTransform->addTransformation(std::make_shared<Scale>(glm::vec3(generateRandomFloat(1.5, 3.0))));
        bushTransform->addTransformation(std::make_shared<Scale>(glm::vec3(generateRandomFloat(15.0, 25.0))));

        glm::vec3 autumnColor = generateAutumnColor();

        DrawableObject tree(treeModel, *treeTransform, treeShaderProgram, true, autumnColor);
        DrawableObject bush(bushModel, *bushTransform, bushShaderProgram, false, glm::vec3(0.1f, 0.8f, 0.2f));

        addObject(tree);
        addObject(bush);
    }

    // Add 5 trees side by side
    for (int i = 0; i < 5; ++i) {
        std::shared_ptr<Transformation> treeTransform = std::make_shared<Transformation>();
        treeTransform->addTransformation(std::make_shared<Translation>(glm::vec3(i * 10.0f, groundLevel, 0.0f)));
        treeTransform->addTransformation(std::make_shared<Scale>(glm::vec3(2.0f)));
        glm::vec3 autumnColor = generateAutumnColor();
        DrawableObject tree(treeModel, *treeTransform, treeShaderProgram, true, autumnColor);
        rotatingTrees.push_back(tree);
        //addObject(tree);
    }
}

void ForestScene::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 lightPos = sceneLight->getPosition();
    glm::vec3 lightColor = sceneLight->getColor();

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

    for (auto& tree : rotatingTrees) {
        std::shared_ptr<Transformation> treeTransform = std::make_shared<Transformation>();
        treeTransform->addTransformation(std::make_shared<Rotation>(0.0f, 1.0f, 0.0f));
        tree.getTransform().addTransformation(treeTransform);
        tree.draw();
    }

    for (const auto& object : objects) {
        if (object.isTree()) {
            treeShaderProgram.use();
            glm::vec3 autumnColor = object.getColor();
            treeShaderProgram.setUniform("objectColor", autumnColor);
            treeShaderProgram.setLightingUniforms(lightPos, viewPos, lightColor, autumnColor);
        }
        else {
            bushShaderProgram.use();
            glm::vec3 bushColor = object.getColor();
            bushShaderProgram.setUniform("objectColor", bushColor);
            bushShaderProgram.setLightingUniforms(lightPos, viewPos, lightColor, bushColor);
        }

        object.draw();
        sceneLight->draw();
    }
}

Camera& ForestScene::getCamera() {
    return camera;
}

void ForestScene::setCamera(Camera& camera) {
    camera.addObserver(&treeShaderProgram);
    camera.addObserver(&bushShaderProgram);
    camera.addObserver(&lightShaderProgram);
}
