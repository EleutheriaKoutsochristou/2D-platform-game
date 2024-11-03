#pragma once
#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
using namespace std;

// Class that manages the sound files of the game(.wav)
class Sounds :public GameObject
{
public:
	std::vector<std::string> sfx;
	string getSounds(string type);
	void setSounds();
};

