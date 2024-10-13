#include "ForestScene.h"
#include "TreeModel.h" // Použití specializované třídy TreeModel
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Transformation.h"
#include <GL/glew.h>

ForestScene::ForestScene() {
    setupScene();
}

void ForestScene::setupScene() {
    Shader vertexShader("forest_vshader.glsl", GL_VERTEX_SHADER);
    Shader fragmentShader("forest_fshader.glsl", GL_FRAGMENT_SHADER);
    ShaderProgram shaderProgram(vertexShader, fragmentShader);

    TreeModel treeModel; // Specifický model pro strom

    for (int i = 0; i < 5; ++i) {
        DrawableObject treeObject(treeModel, shaderProgram);
        Transformation transform;
        transform.translate(i * 2.0f, 0.0f, 0.0f);
        transform.scale(1.0f + i * 0.1f, 1.0f, 1.0f);
        treeObject.setTransformation(transform);
        addObject(treeObject);
    }
}

void ForestScene::render() {
    Scene::render();
}
