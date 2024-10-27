#include "Application.h"
#include "TriangleScene.h"
#include "ForestScene.h"
#include "SphereScene.h"
#include "ShaderShowcaseScene.h"  // Include the new scene

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    Application app(windowWidth, windowHeight);

    TriangleScene triangleScene;
    ForestScene forestScene(100);  // Initialize ForestScene
    SphereScene sphereScene;       // Initialize SphereScene
    ShaderShowcaseScene shaderShowcaseScene; // Initialize ShaderShowcaseScene

    app.setScene(&triangleScene);

    // Run the application with access to all three scenes
    app.run(triangleScene, forestScene, sphereScene, shaderShowcaseScene);

    return 0;
}
