#include <sgg/graphics.h>

#include "gamestate.h"

void draw()
{
    GameState::getInstance()->draw();   //draw lvl
}

void update(float dt)
{
    GameState::getInstance()->update(dt);  // update gamestate
}


int main(int argc, char** argv)
{
    graphics::createWindow(800, 800, "Pixels");
    GameState::getInstance()->init();

    graphics::setDrawFunction(draw); // draw the lvl
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    graphics::setFont("assets\\font.ttf");
    graphics::startMessageLoop();
    graphics::destroyWindow();
	return 0;
}

