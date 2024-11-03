#pragma once
#include <string>
#include <vector> 

class GameState
{
private:
	static GameState* m_unique_instance;

	const std::string m_asset_path = "assets\\";

	// zoom in/out
	const float m_canvas_width  = 5.0f;
	const float m_canvas_height = 5.0f;
	
	class Level * m_current_level = 0;
	class Player* m_player = 0;  
	class Animations* animations = 0;
	class Sounds* sfx = 0;
	
	std::vector<Level*> m_levels;  //Vector of pointers containing the levels we dynamically create to delete after the game is finished
	std::vector<std::vector<std::string> > levels{ {"Menu_1","false","0f","0f","",""},  //List of the 4 levels of the game (2 menu levels, 2 main levels)
		{"Level1","true","-15.0f","-1.0f","Lvl1_Blocks.txt","Lvl1_Dynamic_Blocks.txt"},
		{"Level2","true","-9.0f","-4.8f","Lvl2_Blocks.txt","Lvl2_Dynamic_Blocks.txt"},
		{"Menu_2","false","0f","0f","",""} };
	GameState();

public:
	// players position : starting point
	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;
	bool m_debugging = false;
	int score = 0;   //Keep track of the player's score
	float hp = 0;  //Keep track of the player's health, starting from 0 as full health and 100 as 0 health
	int counter = 0;  //Counter to keep track of the level we want to get from the list of levels
public:
	~GameState();
	static GameState* getInstance();  //Create a new GameState

	bool init();
	void draw();
	void update(float dt);
	void nextLevel();

	std::string getFullAssetPath(const std::string& asset);
	std::string getAssetDir();

	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }

	// get functions for our private pointers to classes
	class Player* getPlayer() { return m_player; }
	class Level* getLevel() { return m_current_level; }
	class Animations* getAnimations() { return animations; }
	class Sounds* getSounds() { return sfx; }
	std::vector<std::vector<std::string> > LevelsList() { return levels; }
};