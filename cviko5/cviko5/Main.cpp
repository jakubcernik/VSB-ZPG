#include "Application.h"
#include "TriangleScene.h"
#include "ForestScene.h"
#include "ForestSceneNight.h"
#include "SphereScene.h"
#include "ShaderShowcaseScene.h"

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    Application app(windowWidth, windowHeight);

    // Scenes initialization
    TriangleScene triangleScene;
    ForestScene forestScene(100);
    SphereScene sphereScene;
    ShaderShowcaseScene shaderShowcaseScene;
    ForestSceneNight forestSceneNight(100);

    app.setScene(&triangleScene);

    app.run(triangleScene, forestScene, sphereScene, shaderShowcaseScene, forestSceneNight);

    return 0;
}
