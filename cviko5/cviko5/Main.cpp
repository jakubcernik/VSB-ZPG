//Main.cpp

#include "Application.h"
#include "ForestScene.h"
#include "SphereScene.h"

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    Application app(windowWidth, windowHeight);

    ForestScene forestScene(100);   // 100 trees and 100 bushes
    SphereScene sphereScene;

    app.setScene(&forestScene);

    app.run(forestScene, sphereScene);

    return 0;
}

