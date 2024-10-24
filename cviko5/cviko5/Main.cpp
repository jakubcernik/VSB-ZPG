//Main.cpp

#include "Application.h"
#include "ForestScene.h"
#include "Scene1.h"

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    Application app(windowWidth, windowHeight);

    ForestScene forestScene(100);   // 100 trees and 100 bushes
    Scene1 scene1;

    forestScene.setCamera(app.camera);
    scene1.setCamera(app.camera);

    app.setScene(&forestScene);

    app.run(forestScene, scene1);

    return 0;
}

