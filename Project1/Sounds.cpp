#include "Sounds.h"
#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Read from a txt file all the names of the .wav items
void Sounds::setSounds() {

	string line;
	ifstream myfile("Sfx.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line)) {
			string s;
			istringstream ss(line);
			vector<string> temp;
			while (ss)
			{
				if (!getline(ss, s, ',')) break;
				sfx.push_back(s);
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

//We get the sound file based on a keyword when calling the function, no multiple items with same name
string Sounds::getSounds(string type) {
	vector<string> List;
	for (const auto& item : sfx) {
		if (item.find(type) != std::string::npos) {
			return m_state->getFullAssetPath(item);
		}
	}
	return "file not found";
}
