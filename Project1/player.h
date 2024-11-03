#pragma once

#include "gameobject.h"
#include <sgg/graphics.h>
#include "box.h"

class Player : public Box, public GameObject
{
	// animated player
	std::vector<std::string> m_sprites;
	graphics::Brush m_brush_player;

	const float m_accel_horizontal = 17.0f;		// running speed
	const float m_accel_vertical = 250.1f;		// jump "speed"
	const float m_max_velocity = 5.0f;			// max speed so it doesnt speed up infin.
	const float m_gravity = 10.0f;				// fall "speed"
public:
	float m_vx = 0.0f;  //public speed so we can access it from different classes
	float m_vy = 0.0f;	


public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	Player(std::string name) : GameObject(name) {}

	
protected:
	void debugDraw();
	
	// dynamic motion control
	void movePlayer(float dt);
};
