#include "Dynamic_Blocks.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "level.h"


//Read blocks from a txt file, create a Dynamic_Blocks item and add it to the dynamic_blocks vector of pointers for the class
std::vector<Dynamic_Blocks*> Dynamic_Blocks::readBlock() {
	std::string txt = m_state->getLevel()->dyn_block_txt;
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
			dynamic_blocks.push_back(new Dynamic_Blocks(stof(temp[0]), stof(temp[1]), stof(temp[2]), stof(temp[3]), temp[4], "false", stoi(temp[5]), temp[6]));
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	return dynamic_blocks;
}

void Dynamic_Blocks::drawBlock(Dynamic_Blocks block)
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

//According to the block type return the block type if there's collision with the player
string Dynamic_Blocks::CheckColls(Dynamic_Blocks block)
{
	if (block.type == "collectibles") {
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersect(block.box))
		{
			return block.type;
		}
	}
	else if (block.type == "Finish") {
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersect(block.box))
		{
			return block.type;
		}
	}
	else if (block.type == "enemy") {
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersect(block.box))
		{
			return block.type;
		}
	}
	return "";
}
Dynamic_Blocks ::~Dynamic_Blocks()
{
	for (auto p_go : dynamic_blocks)
		delete p_go;
}
