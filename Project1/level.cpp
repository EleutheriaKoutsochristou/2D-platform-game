#include "level.h"
#include <sgg/graphics.h>
#include "player.h"
#include "util.h"
#include "Block.h"
#include "Dynamic_Blocks.h"
#include <string>
#include "Animations.h"
#include "Sounds.h"

void Level::update(float dt)
{ 
	//if the player is active(has been initialized/drawn) check for collisions for block and dynamic_block lists
	if (m_state->getLevel()->isActive()) {
		m_state->getPlayer()->update(dt);
		for (auto& obj : m_blocks) {
			blocks->checkCollisionsDown(*obj);
			blocks->checkCollisionSideways(*obj);
		}
		for (auto& obj : d_blocks) {
			if (dyn_blocks->CheckColls(*obj) == "collectibles") {
				//If there's collision with a collectibles item 
				if (obj->points == 0) {  //if the item's points==0 it is a health item therefore we adjust the health(hp) variable of the gamestate
					if(m_state->hp - 10 > 0)   // every enemy does 10 damage so we check if the hp remaining is enough before changing it to avoid going off bounds
						m_state->hp -= 10;   // remove 10 hp( increase the hp counter since when we have 0 hp health bar is full and when we have 100hp health bar is 0)
					else
						m_state->hp = 0; //if we dont have enough health to deduct 10 from we set the hp to 0
					graphics::playSound(m_state->getSounds()->getSounds("heal"), 0.3f);
				}
				else {
					graphics::playSound(m_state->getSounds()->getSounds("coll"), 0.3f);
					m_state->score += obj->points; //if the item is not a health item then we increase the score counter of gamestate according to the item's points
				}
				delete obj;
				d_blocks.erase(std::remove(d_blocks.begin(), d_blocks.end(), obj), d_blocks.end()); // When we interact with a collectible item we dynamically delete it 
			}
			else if (dyn_blocks->CheckColls(*obj) == "Finish") //If the block.type is Finish then we have a collision with the item that is responsible for the level changes
			{													//so we call nextLevel() to get the next one
				graphics::stopMusic();
				m_state->nextLevel();
			}
			else if (dyn_blocks->CheckColls(*obj) == "enemy") {   //If the block.type is an enemy
				graphics::playSound(m_state->getSounds()->getSounds("enemy"), 0.2f); 
				m_state->hp += obj->points;  //adjust the hp variable amount based on the points(damage) of the enemy(All our enemies deal 10 dmg)
				if (m_state->hp == 100) {  //if we reach hp==100(0 health) then reset the score/set the hp to full/decrease the counter and call nextLevel() so the level can restart
					m_state->score = 0;
					m_state->hp = 0;
					m_state->counter -= 1;
					m_state->nextLevel();
				}
			}
		}
	}else{
		float p = 0.5f + fabs(cos(graphics::getGlobalTime() / 700.0f));
		SETCOLOR(brush.fill_color, p, p, p);
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)){
			graphics::stopMusic();
			m_state->nextLevel();
		}
	}
	GameObject::update(dt);
}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();
	float offset_x = m_state->m_global_offset_x / 2.0f + w;
	float offset_y = m_state->m_global_offset_y / 2.0f + h;
	//draw background
	graphics::drawRect(offset_x/3  , offset_y/3,  w*2, w*1.5, m_brush_background);
	//Brushes for the text on the window
	// draw player if the player is visible in that stage
	if (m_state->getLevel()->isActive())
	{
		//Draw the Blocks 
		m_state->getPlayer()->draw();
		for (auto& obj : m_blocks) {
			obj->drawBlock(*obj);
		}
		for (auto& obj : d_blocks) {
			obj->drawBlock(*obj);
		}
		hp_brush.outline_opacity = 0;
		hp_brush.fill_opacity = 1;
		graphics::drawText(m_state->getCanvasWidth() * 0.3f - 1.3f, m_state->getCanvasHeight() * 0.3f - 1.0f, 0.15f, "Score: " + to_string(m_state->score), brush);
		graphics::drawText(m_state->getCanvasWidth() * 0.3f - 1.3f, m_state->getCanvasHeight() * 0.3f - 1.2f, 0.15f, "Health:", brush);
		graphics::drawRect(m_state->getCanvasWidth() * 0.3f - 0.2f - (m_state->hp / 100)/2, m_state->getCanvasHeight() * 0.3f - 1.23f, 1 - m_state->hp/100, 0.1f, hp_brush);
		hp_brush.fill_opacity = 0;
		hp_brush.outline_opacity = 1.0f;
		graphics::drawRect(m_state->getCanvasWidth() * 0.3f - 0.2f, m_state->getCanvasHeight() * 0.3f - 1.23f, 1, 0.1f, hp_brush);

	}
	else if(m_state->getLevel()->getName() == "Menu_1") {
		graphics::drawText(m_state->getCanvasWidth() * 0.3f + 0.4f, m_state->getCanvasHeight() * 0.3f + 0.5f, 0.5f, "Pixels", title_brush);
		graphics::drawText(m_state->getCanvasWidth() * 0.3f - 0.4f, m_state->getCanvasHeight() * 0.3f + 1.0f, 0.25f, "Press space to continue!" , brush);
	}
	else if (m_state->getLevel()->getName() == "Menu_2") {
		graphics::drawText(m_state->getCanvasWidth() * 0.3f + 0.3f, m_state->getCanvasHeight() * 0.3f - 0.5f, 0.5f, "Pixels", title_brush);
		graphics::drawText(m_state->getCanvasWidth() * 0.3f + 0.5f, m_state->getCanvasHeight() * 0.3f + 0.7f, 0.30f, "Score: " + to_string(m_state->score), title_brush);
		graphics::drawText(m_state->getCanvasWidth() * 0.3f + 0.1f, m_state->getCanvasHeight() * 0.3f + 1.0f, 0.2f, "Thank you for playing!", title_brush);
		graphics::drawText(m_state->getCanvasWidth() * 0.3f + 0.4f, m_state->getCanvasHeight() * 0.3f + 1.15f, 0.15f, "Press space to exit", brush);
	
	}

}

void Level::init()
{
	blocks = new Block;
	dyn_blocks = new Dynamic_Blocks;
	// initialize some collidable blocks here.
	m_brush_background.outline_opacity = 0.0f;
	brush.fill_opacity = 1.0f;
	title_brush.outline_width = 0.5f;
	SETCOLOR(title_brush.fill_color, 1, 1, 1);
	SETCOLOR(title_brush.outline_color, 1, 0.5, 0.8);
	SETCOLOR(hp_brush.fill_color, 0.5, 1, 0);
	SETCOLOR(brush.fill_color, 1, 1, 1);
	// Draw different background/get a different sountrack if its a menu/level stage
	if (!m_state->getLevel()->isActive()) {
		m_brush_background.texture = m_state->getAnimations()->getAnimations("Menu")[0];
		graphics::playMusic(m_state->getSounds()->getSounds("Menu"), 0.1f, true);
	}
	else {
		//Initialize the blocks only if its a level stage
		graphics::playMusic(m_state->getSounds()->getSounds(m_state->getLevel()->getName()), 0.1f, true);
		m_brush_background.texture = m_state->getAnimations()->getAnimations(m_state->getLevel()->getName())[0];
		m_blocks = blocks->readBlock();
		d_blocks = dyn_blocks->readBlock();
	}
}


Level::~Level()
{
	for (auto p_go : m_blocks)
		delete p_go;
	for (auto p_go : d_blocks)
		delete p_go;
	delete blocks;
	delete dyn_blocks;
}
