#include "GameplayDisplay.h"
#include "CommunicationLibrary.hpp"

// Declare our game instance
GameplayDisplay game;
CommunicationLibrary comlib;

GameplayDisplay::GameplayDisplay()
    : _scene(NULL), _wireframe(false) {
}

void GameplayDisplay::initialize() {
    comlib.Init(GAMEPLAY);

    // Load game scene from file
    _scene = Scene::load("res/demo.scene");

    // Get the box model and initialize its material parameter values and bindings
    Node* boxNode = _scene->findNode("box");
    Model* boxModel = dynamic_cast<Model*>(boxNode->getDrawable());
    Material* boxMaterial = boxModel->getMaterial();

    // Set the aspect ratio for the scene's camera to match the current resolution
    _scene->getActiveCamera()->setAspectRatio(getAspectRatio());
}

void GameplayDisplay::finalize() {
    SAFE_RELEASE(_scene);
}

void GameplayDisplay::update(float elapsedTime) {
    // Rotate model
   // _scene->findNode("box")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));

    comlib.Receive();
   // _scene->findNode("box")->setTranslationX(comlib.GetMesh().transformation[0][0]);
}

void GameplayDisplay::render(float elapsedTime) {
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);

    // Visit all the nodes in the scene for drawing
    _scene->visit(this, &GameplayDisplay::drawScene);
}

bool GameplayDisplay::drawScene(Node* node) {
    // If the node visited contains a drawable object, draw it
    Drawable* drawable = node->getDrawable();
    if (drawable)
        drawable->draw(_wireframe);

    return true;
}

void GameplayDisplay::keyEvent(Keyboard::KeyEvent evt, int key) {
    if (evt == Keyboard::KEY_PRESS) {
        switch (key) {
        case Keyboard::KEY_ESCAPE:
            exit();
            break;
        }
    }
}

void GameplayDisplay::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex) {
    switch (evt) {
    case Touch::TOUCH_PRESS:
        _wireframe = !_wireframe;
        break;
    case Touch::TOUCH_RELEASE:
        break;
    case Touch::TOUCH_MOVE:
        break;
    };
}
