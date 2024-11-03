#pragma once
#pragma once
#include <string>
#include "gamestate.h"

class GameObject 
{
	static int m_next_id;
	
protected:
	class GameState* m_state;
	std::string m_name;
	int m_id = 0;
	bool m_active = true;

public:
	GameObject(const std::string& name = "");
	virtual void update(float dt) {}  //use virtual type to ensure we use the functions of the class we want(lvl/player) and not of GameState
	virtual void init() {}
	virtual void draw() {}
	virtual ~GameObject() {}
	bool isActive() { return m_active; }
	void setActive(bool a) { m_active = a; }
	std::string getName() { return m_name; }
};
