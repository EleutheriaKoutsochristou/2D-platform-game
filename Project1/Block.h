#pragma once
#include "gameobject.h"
#include <sgg/graphics.h>
#include "box.h"
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include<sstream>
#include "util.h"

using namespace std;

class Block : public Box, public GameObject
{
private:
	// add some collidable blocks
	std::vector<Block*> blocks;
protected:  
	//protected variables so the derived class Dynamic_Blocks has access to them
	graphics::Brush block_brush;
	graphics::Brush block_brush_debug;
	float pos_x = 0.0f;
	float pos_y = 0.0f;
	float width = 0.0f;
	float height = 0.0f;
	string png_name = "";
	bool collision = false;
	Box box;
public:
	std::vector<Block*>readBlock();
	void drawBlock(Block block);
	void checkCollisionsDown(Block block);
	void checkCollisionSideways(Block block);
	Block() {}
	~Block();
	Block(float x, float y, float w, float h, string png_name,string col) {
		this->pos_x=x;
		this->pos_y=y;
		this->width=w;
		this->height=h;
		this->png_name = png_name;
		istringstream(col) >> std::boolalpha >> collision;
		this->box = Box(pos_x, pos_y, width, height);

	}
};