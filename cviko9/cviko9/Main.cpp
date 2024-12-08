// Author: Jakub Černík
// Login: CER0548
#include "Application.h"
#include "TriangleScene.h"
#include "ForestScene.h"
#include "ForestSceneNight.h"
#include "SphereScene.h"
#include "ShaderShowcaseScene.h"
#include "MaterialScene.h"

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    Application app(windowWidth, windowHeight);

    TriangleScene triangleScene;
    ForestScene forestScene(200);
    SphereScene sphereScene;
    ShaderShowcaseScene shaderShowcaseScene;
    ForestSceneNight forestSceneNight(100);
    MaterialScene materialScene;

    app.setScene(&triangleScene);

    app.run(triangleScene, forestScene, sphereScene, shaderShowcaseScene, forestSceneNight, materialScene);

    return 0;
}
