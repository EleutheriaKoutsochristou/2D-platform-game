#pragma once

#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "player.h"
#include "Block.h"
#include "Dynamic_Blocks.h"

class Level : public GameObject
{
private:
	graphics::Brush m_brush_background;
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;
	graphics::Brush hp_brush;
	graphics::Brush brush;
	graphics::Brush title_brush;

	//static objects that wont be deleted in the level
	//std::vector<GameObject*> m_static_objects;
	//dynamic objects 
	//std::list<GameObject*> m_dynamic_objects;
	
	//void drawBlock(int i,Box box);
	// add some collidable blocks
	std::vector<Block*> m_blocks;
	std::vector<Dynamic_Blocks*> d_blocks;

	class Dynamic_Blocks* dyn_blocks;
	class Block* blocks;
	
	float m_center_x = 5.0f;
	float m_center_y = 5.0f;


public:
	std::string player_active; // Draw or not the player
	float player_x; // Where to draw the player x/y coords
	float player_y;
	//float score_x; // Where to draw the score x/y coords
	//float score_y;
	std::string dyn_block_txt;
	std::string block_txt; // Different txt files for each level
	std::string name;
	void update(float dt) override;
	void draw() override;
	void init() override;
	//std::string getName() { return m_name; }
	//Level(const std::string & name = "Level0");
	Level(std::string name,std::string p_active,float p_x,float p_y, std::string block_txt, std::string dyn_block_txt) 
		: player_active(p_active), player_x(p_x), player_y(p_y), block_txt(block_txt), dyn_block_txt(dyn_block_txt)
	{
		GameObject::m_name = name;
		if (p_active == "false") {
			GameObject::m_active = false;
		}	
	}
	~Level() override;

};