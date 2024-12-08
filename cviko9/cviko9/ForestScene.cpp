// ForestScene.cpp

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
#include <SOIL.h>
#include <glm/gtc/type_ptr.hpp>

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

using namespace std;

inline float generateRandomFloat(float min, float max) 
{
    static default_random_engine engine{ random_device{}() };
    uniform_real_distribution<float> distribution(min, max);
    return distribution(engine);
}

inline glm::vec3 generateRandomVec3(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) 
{
    static default_random_engine engine{ random_device{}() };
    uniform_real_distribution<float> distX(minX, maxX);
    uniform_real_distribution<float> distY(minY, maxY);
    uniform_real_distribution<float> distZ(minZ, maxZ);

    return glm::vec3(distX(engine), distY(engine), distZ(engine));
}

inline glm::vec3 generateAutumnColor() 
{
    static default_random_engine engine{ random_device{}() };
    uniform_real_distribution<float> redDistribution(0.5f, 1.0f);
    uniform_real_distribution<float> greenDistribution(0.3f, 0.6f);
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
    skyboxModel(),
    houseModel("house.obj"),
    loginModel("login1.obj"),
    treeShaderProgram("tree_vertex_shader.glsl", "tree_fragment_shader.glsl"),
    bushShaderProgram("bush_vertex_shader.glsl", "bush_fragment_shader.glsl"),
    groundShaderProgram("ground_vertex.glsl", "ground_fragment.glsl"),
    skyboxShaderProgram("skybox_vertex.glsl", "skybox_fragment.glsl"),
    lightShaderProgram("light_vertex.glsl", "light_fragment.glsl"),
    houseShaderProgram("house_vertex.glsl", "house_fragment.glsl"),
    camera(glm::vec3(0.0f, 50.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -45.0f),
    flashlight(camera.getPosition(), camera.getFront(), glm::vec3(0.3f, 0.5f, 1.0f), lightShaderProgram, 0.0f, 12.5f, 1),
    groundObject(groundModel, new Transformation(), groundShaderProgram, false, glm::vec3(1.0f, 1.0f, 1.0f)),
    skyboxObject(skyboxModel, new Transformation(), skyboxShaderProgram, false, glm::vec3(1.0f, 1.0f, 1.0f)),
    houseObject(nullptr),
    loginObject(nullptr)
{
    // Light( position, direction, color, shader, scale, angle, type)
    lights.push_back(Light(glm::vec3(-50.0f, 20.0f, 20.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.3f, 0.5f, 1.0f), lightShaderProgram, 1.0f, 0.0f, 0));
    lights.push_back(Light(glm::vec3(50.0f, 10.0f, 10.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.3f, 0.5f, 1.0f), lightShaderProgram, 1.0f, 20.0f, 1));

    initializeObservers();
    createForest(treeCount);

    // Na�ten� textur
    groundTexture = loadTexture("grass.png");
    houseTexture = loadTexture("house.png");

    skyboxTexture = loadSkyboxTexture({ "posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg" });

    if (!groundTexture || !houseTexture || !skyboxTexture) {
        std::cerr << "Failed to load one or more textures!" << std::endl;
    }

    configureShader(groundShaderProgram, "texture1", 0);
    configureShader(houseShaderProgram, "textureUnitID", 0);
    configureShader(skyboxShaderProgram, "UISky", 0);

}

ForestScene::~ForestScene() {}

void ForestScene::initializeObservers() {
    camera.addObserver(&treeShaderProgram);
    camera.addObserver(&bushShaderProgram);
    camera.addObserver(&lightShaderProgram);
    camera.addObserver(&groundShaderProgram);
    camera.addObserver(&houseShaderProgram);
}

GLuint ForestScene::loadTexture(const std::string& filename)
{
    GLuint textureID = SOIL_load_OGL_texture(
        filename.c_str(),
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (!textureID) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return 0;
    }

    // Nastaven� parametr� textury
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}



GLuint ForestScene::loadSkyboxTexture(const std::vector<std::string>& faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (size_t i = 0; i < faces.size(); ++i) {
        int width, height, channels;
        unsigned char* image = SOIL_load_image(faces[i].c_str(), &width, &height, &channels, SOIL_LOAD_RGB);

        if (image) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            SOIL_free_image_data(image);
        }
        else {
            std::cerr << "Failed to load skybox texture: " << faces[i] << std::endl;
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
            return 0;
        }
    }

    // Nastaven� parametr� skyboxu
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0); // Unbind
    return textureID;
}



void ForestScene::configureShader(ShaderProgram& shader, const std::string& textureUniform, int textureUnit) {
    shader.use();
    shader.setUniform(textureUniform.c_str(), textureUnit);
    shader.free();
}


void ForestScene::createForest(int treeCount) {
    float groundLevel = 0.0f;

    for (int i = 0; i < treeCount; ++i) {
        Transformation* treeTransform = new Transformation();
        glm::vec3 treePosition = generateRandomVec3(-150.0f, 150.0f, groundLevel, groundLevel, -150.0f, 150.0f);

        while (treePosition.x > -30.0f && treePosition.x < 30.0f && treePosition.z > -75.0f && treePosition.z < 75.0f) {
            treePosition = generateRandomVec3(-150.0f, 150.0f, groundLevel, groundLevel, -150.0f, 150.0f);
        }

        float randomRotationY = generateRandomFloat(0.0f, 360.0f);
        glm::vec3 scaleValue = glm::vec3(generateRandomFloat(1.5f, 3.0f));

        treeTransform->addTransformation(new Translation(treePosition));
        treeTransform->addTransformation(new Rotation(0.0f, randomRotationY, 0.0f));
        treeTransform->addTransformation(new Scale(scaleValue));

        DrawableObject tree(treeModel, treeTransform, treeShaderProgram, true, generateAutumnColor());
        addObject(tree);
    }
    for(int i = 0; i < 200; i++)
	{
		Transformation* bushTransform = new Transformation();
		glm::vec3 bushPosition = generateRandomVec3(-150.0f, 150.0f, groundLevel, groundLevel, -150.0f, 150.0f);

		while (bushPosition.x > -30.0f && bushPosition.x < 30.0f && bushPosition.z > -75.0f && bushPosition.z < 75.0f) {
			bushPosition = generateRandomVec3(-150.0f, 150.0f, groundLevel, groundLevel, -150.0f, 150.0f);
		}

		float randomRotationY = generateRandomFloat(0.0f, 360.0f);
		glm::vec3 scaleValue = glm::vec3(generateRandomFloat(10.0f, 15.0f));

		bushTransform->addTransformation(new Translation(bushPosition));
		bushTransform->addTransformation(new Rotation(0.0f, randomRotationY, 0.0f));
		bushTransform->addTransformation(new Scale(scaleValue));

		DrawableObject bush(bushModel, bushTransform, bushShaderProgram, false, generateAutumnColor());
		addObject(bush);
	}

    // Create rotating trees
    for (int i = 0; i < 5; ++i) {
        float* angle = new float(0.0f);
        rotationAngles.push_back(angle);

        Transformation* treeTransform = new Transformation();
        treeTransform->addTransformation(new Translation(glm::vec3(i * 10.0f, groundLevel, 0.0f)));
        treeTransform->addTransformation(new Translation(glm::vec3(50.0f, 0.0f, 20.0f)));
        treeTransform->addDynamicRotation(angle, glm::vec3(0, 1, 0)); // Dynamic rotation
        treeTransform->addTransformation(new Scale(glm::vec3(2.0f)));

        DrawableObject tree(treeModel, treeTransform, treeShaderProgram, true, generateAutumnColor());
        rotatingTrees.push_back(tree);
    }

    // House transformation
    Transformation* houseTransform = new Transformation();
    houseTransform->addTransformation(new Translation(glm::vec3(0.0f, 0.0f, 0.0f)));
    houseTransform->addTransformation(new Scale(glm::vec3(5.0f)));

    // Login transformation
    float* loginAngle = new float(0.0f);
    rotationAngles.push_back(loginAngle);

    Transformation* loginTransform = new Transformation();
    loginTransform->addTransformation(new Translation(glm::vec3(-5.0f, 10.0f, 0.0f)));
    loginTransform->addDynamicRotation(loginAngle, glm::vec3(0, 1, 0));
    loginTransform->addTransformation(new Scale(glm::vec3(5.0f)));

    houseObject = new DrawableObject(houseModel, houseTransform, houseShaderProgram, false, glm::vec3(1.0f, 1.0f, 1.0f));
    loginObject = new DrawableObject(loginModel, loginTransform, houseShaderProgram, false, glm::vec3(1.0f, 1.0f, 1.0f));
}

void ForestScene::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw ground
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    groundShaderProgram.use();
    setLightingUniforms(groundShaderProgram, viewPos);
    groundObject.draw();
    groundShaderProgram.free();

    // Draw plants
    for (const auto& object : objects) {
        if(object.isTree())
		{
			treeShaderProgram.use();
			treeShaderProgram.setUniform("objectColor", object.getColor());
			setLightingUniforms(treeShaderProgram, viewPos);
			object.draw();
			treeShaderProgram.free();
		}
		else
		{
			bushShaderProgram.use();
			bushShaderProgram.setUniform("objectColor", object.getColor());
			setLightingUniforms(bushShaderProgram, viewPos);
			object.draw();
			bushShaderProgram.free();
		}
    }

    // Draw rotating trees
    for (const auto& tree : rotatingTrees) {
        treeShaderProgram.use();
        treeShaderProgram.setUniform("objectColor", tree.getColor());
        setLightingUniforms(treeShaderProgram, viewPos);
        tree.draw();
        treeShaderProgram.free();
    }

    rotateDynamicly(0.016f); // 0.016f = 60 FPS

    
    // Draw the house
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, houseTexture);

    houseShaderProgram.use();
    houseShaderProgram.setUniform("textureUnitID", 0);
    setLightingUniforms(houseShaderProgram, viewPos);
    houseObject->draw();
    houseShaderProgram.free();

    //Draw the login with ground texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, groundTexture);

    houseShaderProgram.use();
    houseShaderProgram.setUniform("textureUnitID", 0);
    loginObject->draw();
    houseShaderProgram.free();


    // Draw lights
    for (auto& light : lights) {
        light.draw();
    }

    flashlight.draw();

    // Draw the skybox last
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);

    skyboxShaderProgram.use();

    glm::mat4 viewMatrix = glm::mat4(glm::mat3(view)); // Remove translation from the view matrix

    skyboxShaderProgram.setUniform("viewMatrix", viewMatrix);
    skyboxShaderProgram.setUniform("projectionMatrix", projection);

    // Bind the cubemap texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);

    skyboxObject.draw();

    skyboxShaderProgram.free();

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}

void ForestScene::rotateDynamicly(float deltaTime) {
    for (float* angle : rotationAngles) {
        *angle += 45.0f * deltaTime; // Rotate 45 degrees per second
    }
}


void ForestScene::setLightingUniforms(ShaderProgram& shader, const glm::vec3& viewPos) {
    shader.use();
    shader.setUniform("viewPos", viewPos);
    shader.setUniform("numLights", static_cast<int>(lights.size() + 1));

    for (int i = 0; i < lights.size(); ++i) {
        std::string baseName = "lights[" + std::to_string(i) + "]";
        shader.setUniform((baseName + ".position").c_str(), lights[i].getPosition());
        shader.setUniform((baseName + ".direction").c_str(), lights[i].getDirection());
        shader.setUniform((baseName + ".color").c_str(), lights[i].getColor());
        shader.setUniform((baseName + ".angle").c_str(), lights[i].getAngle());
        shader.setUniform((baseName + ".type").c_str(), lights[i].getType());
    }

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
