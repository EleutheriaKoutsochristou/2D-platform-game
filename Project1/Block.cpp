#include "Block.h"
#include <sgg/graphics.h>
#include "level.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Sounds.h"

//Read blocks from a txt file, create a Block item and add it to the blocks vector of pointers for Block class
std::vector<Block*> Block::readBlock() {
	std::string txt = m_state->getLevel()->block_txt;
	string line;
	ifstream myfile(txt);
	if (myfile.is_open())
	{
		while (getline(myfile, line)) {
			string s;
			istringstream ss(line);
			vector<string> temp;
			while (ss)
			{
				if (!getline(ss, s, ',')) break;
				temp.push_back(s);
			}
			blocks.push_back(new Block(stof(temp[0]), stof(temp[1]), stof(temp[2]), stof(temp[3]), temp[4], temp[5]));
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	return blocks;
}

void Block::drawBlock(Block block)
{
	block_brush.outline_opacity = 0.0f;
	block_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(block_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);
	Box& box = block.box;

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;

	block_brush.texture = m_state->getFullAssetPath(block.png_name);

	graphics::drawRect(x, y, block.width, block.height, block_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, block.width, block.height, block_brush_debug);
}

void Block::checkCollisionsDown(Block block)
{
		if (block.collision) {
			float offset = 0.0f;
			if (offset = m_state->getPlayer()->intersectDown(block.box)) //check if collision down
			{
				m_state->getPlayer()->m_pos_y += offset;  //update players position according to the offset of the function

				// add sound event
				// play the sound effect whenever there is a collision(gravity)
				if (m_state->getPlayer()->m_vy > 1.0f) // we want the sound to play only when the player jumped(had speed vertically)
					graphics::playSound(m_state->getSounds()->getSounds("grass"), 1.0f); //1.0f is the sound volume, 3rd variable for looping

				m_state->getPlayer()->m_vy = 0.0f;   // reduce the speed to 0 when collision
				return; //when we get a collision stop 
			}
		}
}

void Block::checkCollisionSideways(Block block){
		if (block.collision) {
			float offset = 0.0f;
			if (offset = m_state->getPlayer()->intersectSideways(block.box))
			{
				m_state->getPlayer()->m_pos_x += offset;
				m_state->getPlayer()->m_vx = 0.00001f;
				return;
			}
		}
}

Block::~Block()
{
	for (auto p_go :blocks)
		delete p_go;
}
