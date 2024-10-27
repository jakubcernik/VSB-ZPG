#include "Application.h"
#include "ForestScene.h"
#include "SphereScene.h"
#include "ShaderShowcaseScene.h"  // Include the new scene

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    Application app(windowWidth, windowHeight);

    ForestScene forestScene(100);  // Initialize ForestScene
    SphereScene sphereScene;       // Initialize SphereScene
    ShaderShowcaseScene shaderShowcaseScene; // Initialize ShaderShowcaseScene

    app.setScene(&forestScene);

    // Run the application with access to all three scenes
    app.run(forestScene, sphereScene, shaderShowcaseScene);

    return 0;
}
