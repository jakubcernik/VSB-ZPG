//Main.cpp

#include "Application.h"
#include "ForestScene.h"

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    Application app(windowWidth, windowHeight);

    ForestScene forestScene(100);   // 100 trees and 100 bushes

    app.setScene(&forestScene);

    app.run();

    return 0;
}

