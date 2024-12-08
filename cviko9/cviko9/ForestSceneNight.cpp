// ForestSceneNight.cpp

#include "ForestSceneNight.h"
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

ForestSceneNight::ForestSceneNight(int treeCount)
    : treeModel(),
    bushModel(),
    treeShaderProgram("tree_night_vertex.glsl", "tree_night_fragment.glsl"),
    bushShaderProgram("bush_night_vertex.glsl", "bush_night_fragment.glsl"),
    lightShaderProgram("light_vertex.glsl", "light_fragment.glsl"),
    fireflyShaderProgram("firefly_vertex.glsl", "firefly_fragment.glsl"),
    //Camera(startPosition, startUp, startYaw, startPitch);
    camera(glm::vec3(0.0f, 50.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -45.0f) {

    initializeSceneLight();
    createForest(treeCount);
    initializeFireflies(10);
}

void ForestSceneNight::initializeSceneLight() {
    sceneLight = new Light(
        glm::vec3(50.0f, 150.0f, 10.0f),  // position
        glm::vec3(1.0f, -1.0f, 0.0f),     // direction
        glm::vec3(0.0f, 1.0f, 0.3f),      // color
        lightShaderProgram,               // lightShader
        10.0f,                            // scale
        12.5f,                            // angle
        1                                 // type
    );

    camera.addObserver(&treeShaderProgram);
    camera.addObserver(&bushShaderProgram);
    camera.addObserver(&lightShaderProgram);
    camera.addObserver(&fireflyShaderProgram);
}

void ForestSceneNight::initializeFireflies(int count) {
    for (int i = 0; i < count; ++i) {
        glm::vec3 fireflyPosition = generateRandomVec3(-100.0f, 100.0f, 0.0f, 20.0f, -100.0f, 100.0f);
        Light* firefly = new Light(
            fireflyPosition,               // position
            glm::vec3(0.0f, 1.0f, 0.0f),   // direction
            glm::vec3(0.0f, 1.0f, 0.2f),   // color
            fireflyShaderProgram,          // lightShader
            0.2f,                          // scale
            12.5f,                         // angle
            1                              // type
        );
        fireflies.push_back(firefly);
    }
}

void ForestSceneNight::createForest(int treeCount) {
    float groundLevel = 0.0f;

    for (int i = 0; i < treeCount; ++i) {
        // Use raw pointers
        Transformation* treeTransform = new Transformation();
        Transformation* bushTransform = new Transformation();

        glm::vec3 treeRandomPosition = generateRandomVec3(-100.0f, 100.0f,
            groundLevel, groundLevel, -100.0f, 100.0f);
        glm::vec3 bushRandomPosition = generateRandomVec3(-100.0f, 100.0f,
            groundLevel, groundLevel, -100.0f, 100.0f);

        // Add transformations using raw pointers
        treeTransform->addTransformation(new Translation(treeRandomPosition));
        bushTransform->addTransformation(new Translation(bushRandomPosition));

        float randomRotationY = generateRandomFloat(0.0f, 360.0f);
        treeTransform->addTransformation(new Rotation(0.0f, randomRotationY, 0.0f));
        bushTransform->addTransformation(new Rotation(0.0f, randomRotationY, 0.0f));

        treeTransform->addTransformation(new Scale(glm::vec3(generateRandomFloat(1.5f, 3.0f))));
        bushTransform->addTransformation(new Scale(glm::vec3(generateRandomFloat(15.0f, 25.0f))));

        glm::vec3 autumnColor = generateAutumnColor();

        // Pass the Transformation pointers directly
        DrawableObject tree(treeModel, treeTransform, treeShaderProgram, true, autumnColor);
        DrawableObject bush(bushModel, bushTransform, bushShaderProgram, false, glm::vec3(0.1f, 0.8f, 0.2f));

        addObject(tree);
        addObject(bush);

        // Store transformations for cleanup
        transformations.push_back(treeTransform);
        transformations.push_back(bushTransform);
    }
}


void ForestSceneNight::updateFireflies(float deltaTime) {
    for (auto& firefly : fireflies) {
        glm::vec3 position = firefly->getPosition();
        position += generateRandomVec3(-3.0f, 3.0f, -3.0f, 3.0f, -3.0f, 3.0f) * deltaTime;
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
    updateFireflies(0.016f); // 0.016f = 60 FPS

    // Pass fireflies to shader
    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;

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

        if (object.isTree()) {
			treeShaderProgram.free();
		}
		else {
			bushShaderProgram.free();
		}
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
