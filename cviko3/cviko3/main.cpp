#define GLM_ENABLE_EXPERIMENTAL
#include "Application.h"
#include "ForestScene.h"

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    Application app(windowWidth, windowHeight);

    std::string modelPath = "tree.h";
    std::string vertexShaderPath = "vertex_shader.glsl";
    std::string fragmentShaderPath = "fragment_shader.glsl";

    ForestScene forestScene(modelPath, vertexShaderPath, fragmentShaderPath, 100);

    // Nastavení scény pro aplikaci
    app.setScene(&forestScene);

    app.run();

    return 0;
}

