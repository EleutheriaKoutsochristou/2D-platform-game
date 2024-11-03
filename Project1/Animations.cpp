#include "Animations.h"
#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void Animations::setAnimations() {
	
	string line;
	ifstream myfile("Animations.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line)) {
			string s;
			istringstream ss(line);
			vector<string> temp;
			while (ss)
			{
				if (!getline(ss, s, ',')) break;
				sprites.push_back(s);
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";
	
}

//We get the animation based on a keyword when calling the function, if multiple items with the same name return them all(for example running animation sprites)
std::vector<string> Animations::getAnimations(string type){
	vector<string> List;
	for (const auto& item : sprites){
		if (item.find(type) != std::string::npos) {
			List.push_back(m_state->getFullAssetPath(item));
		}
	}
	return List;
}
