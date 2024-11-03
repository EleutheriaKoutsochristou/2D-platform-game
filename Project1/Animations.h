#pragma once
#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
using namespace std;

//Class that manages the animations of the game
class Animations:public GameObject
{
public:
	std::vector<std::string> sprites; // Store the images
	std::vector<string> getAnimations(string type); //Return the images
	void setAnimations(); //Read the animations from a txt file
};

