#include "gamestate.h"
#include "level.h"
#include "player.h"
#include "Animations.h"
#include "Sounds.h"
#include <thread>
#include <chrono> // sleep_for()
using namespace std::chrono_literals;

GameState::GameState()
{
}

// destructor
GameState::~GameState()
{
	for (auto p_go : m_levels)
		delete p_go;
	delete animations;
	delete sfx;
}


// Create new game instance if none exists/ if it already exists return it
GameState* GameState::getInstance()
{
	if (!m_unique_instance)
	{
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}

bool GameState::init()
{
	// Initialize the 2 classes that manage the animation and sound files
	animations = new Animations();
	animations->setAnimations();
	sfx = new Sounds();
	sfx->setSounds();
	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(m_asset_path + "OpenSans-Regular.ttf");
	// call the function nextLevel() to initialize the first level
	nextLevel();
	return true;
}

void GameState::draw()
{
	if (!m_current_level)
		return;

	m_current_level->draw();
}

void GameState::update(float dt)
{
	// Skip an update if a long delay is detected 
	// to avoid messing up the collision simulation
	if (dt > 500) // ms
		return;
	
	// Avoid too quick updates
	// We do this to counter the jerking motion when moving(too fast updates=not enough dt(time))
	float sleep_time = std::max(20.0f - dt, 0.0f);
	if (sleep_time > 0.0f)
	{
		// to adjust fps adjust the sleeping time of the thread
		std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));
	}
	if (!m_current_level)
		return;
	m_current_level->update(dt);   //call the current lvl update function
	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

// initialize the variable
GameState* GameState::m_unique_instance = nullptr;

// Function that manages the level creation and which level to create each time
void GameState::nextLevel() {
	//If we are on the last level of the list end the messageloop and stop the program
	if (counter == levels.size()) { 
		graphics::stopMessageLoop();
	}
	//Create a level according to the counter value, draw the player only if the variable of the level isActive() is true(for menu levels)
	else {
		m_levels.push_back(m_current_level = new Level(levels[counter][0], levels[counter][1], stof(levels[counter][2]), stof(levels[counter][3]), levels[counter][4], levels[counter][5]));
		m_current_level->init();
		counter = counter + 1; // ++ the counter to get the next level on the next loop
		if (m_current_level->isActive()) {
			m_player = new Player("Player");
			m_player->init();
		}
	}
}
