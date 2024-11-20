#include "ForestScene.h"
#include "Transformation.h"
#include "Translation.h"
#include "Rotation.h"
#include "Scale.h"
#include "Light.h"
#include "PlainModel.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>
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
    groundModel(),
    treeShaderProgram("tree_vertex_shader.glsl", "tree_fragment_shader.glsl"),
    bushShaderProgram("bush_vertex_shader.glsl", "bush_fragment_shader.glsl"),
    groundShaderProgram("ground_vertex.glsl", "ground_fragment.glsl"),
    lightShaderProgram("light_vertex.glsl", "light_fragment.glsl"),
    camera(glm::vec3(0.0f, 50.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -45.0f),
    flashlight(camera.getPosition(), camera.getFront(), glm::vec3(0.3f, 0.5f, 1.0f), lightShaderProgram, 0.0f, 12.5f, 1) {

    lights.push_back(Light(glm::vec3(-50.0f, 20.0f, 20.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.3f, 0.5f, 1.0f), lightShaderProgram, 1.0f, 0.0f, 0));
    lights.push_back(Light(glm::vec3(50.0f, 10.0f, 10.0f), glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.3f, 0.5f, 1.0f), lightShaderProgram, 1.0f, 20.0f, 1));

    for (auto& light : lights) {
        light.addObserver(&treeShaderProgram);
        light.addObserver(&bushShaderProgram);
    }

    flashlight.addObserver(&treeShaderProgram);
    flashlight.addObserver(&bushShaderProgram);

    camera.addObserver(&treeShaderProgram);
    camera.addObserver(&bushShaderProgram);
    camera.addObserver(&lightShaderProgram);

    createForest(treeCount);

    // Load ground texture
    groundTexture = SOIL_load_OGL_texture(
        "grass.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if (groundTexture == 0) {
        std::cerr << "Failed to load texture: " << SOIL_last_result() << std::endl;
        return;
    }

    // Bind the ground texture to the first texture unit
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, groundTexture);

    // Set the texture unit to the fragment shader
    groundShaderProgram.use();
    groundShaderProgram.setUniform("texture1", 0);
    groundShaderProgram.free();
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
    }
}

void ForestScene::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Bind ground texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, groundTexture);

    // Render ground
    groundShaderProgram.use(); // Use the ground shader program
    groundShaderProgram.setUniform("texture1", 0);
    groundShaderProgram.setUniform("projection", projection);
    groundShaderProgram.setUniform("view", view);
    groundShaderProgram.setUniform("model", glm::mat4(1.0f)); // Assuming the ground is not transformed

    glBindVertexArray(groundModel.getVAO());
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    // Render other objects
    for (const auto& object : objects) {
        if (object.isTree()) {
            treeShaderProgram.use();
            glm::vec3 autumnColor = object.getColor();
            treeShaderProgram.setUniform("objectColor", autumnColor);
            setLightingUniforms(treeShaderProgram, viewPos);
            object.draw();
            treeShaderProgram.free();
        }
        else {
            bushShaderProgram.use();
            glm::vec3 bushColor = object.getColor();
            bushShaderProgram.setUniform("objectColor", bushColor);
            setLightingUniforms(bushShaderProgram, viewPos);
            object.draw();
            bushShaderProgram.free();
        }
    }

    // Draw the light sources after all objects are drawn
    for (auto& light : lights) {
        light.draw();
    }

    // Draw the flashlight
    flashlight.draw();
}

void ForestScene::setLightingUniforms(ShaderProgram& shader, const glm::vec3& viewPos) {
    shader.use();
    shader.setUniform("viewPos", viewPos);
    shader.setUniform("numLights", static_cast<int>(lights.size() + 1)); // +1 for the flashlight

    for (int i = 0; i < lights.size(); ++i) {
        std::string baseName = "lights[" + std::to_string(i) + "]";
        shader.setUniform((baseName + ".position").c_str(), lights[i].getPosition());
        shader.setUniform((baseName + ".direction").c_str(), lights[i].getDirection());
        shader.setUniform((baseName + ".color").c_str(), lights[i].getColor());
        shader.setUniform((baseName + ".angle").c_str(), lights[i].getAngle());
        shader.setUniform((baseName + ".type").c_str(), lights[i].getType());
    }

    // Set flashlight uniforms
    std::string baseName = "lights[" + std::to_string(lights.size()) + "]";
    shader.setUniform((baseName + ".position").c_str(), camera.getPosition());
    shader.setUniform((baseName + ".direction").c_str(), camera.getFront());
    shader.setUniform((baseName + ".color").c_str(), flashlight.getColor());
    shader.setUniform((baseName + ".angle").c_str(), flashlight.getAngle());
    shader.setUniform((baseName + ".type").c_str(), flashlight.getType());
}

Camera& ForestScene::getCamera() {
    return camera;
}

void ForestScene::setCamera(Camera& camera) {
    camera.addObserver(&treeShaderProgram);
    camera.addObserver(&bushShaderProgram);
    camera.addObserver(&lightShaderProgram);
}
