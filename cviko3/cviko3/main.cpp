#include "Application.h"
#include "ForestScene.h"

int main() {
    Application app;

    if (!app.initialize()) {
        return -1;
    }

    auto forestScene = std::make_shared<ForestScene>();
    app.addScene(forestScene);

    while (!app.shouldClose()) {

        app.renderScene();
        app.pollEvents();
    }

    app.terminate();
    return 0;
}
