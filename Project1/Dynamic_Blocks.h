#pragma once
#include "Block.h"

class Dynamic_Blocks: public Block
{
public:
	int points = 0;
	string type;
	string txt = "Dynamic_Blocks.txt";
	std::vector<Dynamic_Blocks*> dynamic_blocks;
	std::vector<Dynamic_Blocks*>readBlock();
	void drawBlock(Dynamic_Blocks block);
	string CheckColls(Dynamic_Blocks block);
	~Dynamic_Blocks();
	Dynamic_Blocks(float x, float y, float w, float h, string png_name,string col,int points,string type)
		:Block(x, y, w, h, png_name, col){
		this->points = points;
		this->type = type;
	}
	Dynamic_Blocks() {}
};
