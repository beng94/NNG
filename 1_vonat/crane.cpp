#include "crane.h"
#include <utility>

void Crane::sort(){
	std::vector<std::pair<int, int>> changepairs;
	while (begin != end){
		changepairs.push_back(findbestchange_front());
		changepairs.push_back(findbestchange_back());
		changepairs.push_back(findbestchange_full());
		//current = stringflip(current, changepair[0], changepair[1]); //Flips the working string
	//	doneupto += changepair[1] - changepair[0]; //The amount of characters we flipped, the string is done up to this point
		std::cout << current << std::endl;
	}
}

std::string Crane::stringflip(std::string string, int b, int e){
	std::vector<std::string> substrings;
	std::string substring = string.substr(0, b);
	substrings.push_back(substring);
	substring = string.substr(b, e - b);
	substring = std::string(substring.rbegin(), substring.rend());
	substrings.push_back(substring);
	substring = string.substr(e);
	substrings.push_back(substring); //We create the 3 substrings, the part before the flip, the flipped part and the end
	return substrings[0] + substrings[1] + substrings[2];
}

std::pair<int, int> Crane::findbestchange_front(){
	std::vector<int> returnval;
	int maxindex = 0, firstval;
	for (int i = 0; i < current.size() - 1; i++){
		for (int j = i + 1; j < current.size(); j++){
			std::string string = stringflip(current, i, j);
			int matching = matchingchars(string, target);
			if (matching > maxindex){
				maxindex = matching;
				firstval = i;
			}
		}
	}
//	returnval.push_back(doneupto);
	returnval.push_back(firstval);
	return std::pair<int, int>(1, 1);
}

std::pair<int, int> findbestchange_back(){
	return std::pair<int, int>(1, 1);
}

std::pair<int, int> findbestchange_full(){
	return std::pair<int, int>(1, 1);

}

int Crane::matchingchars(std::string s1, std::string s2){
	int returnval = 0;
	for (int i = 0; i < s1.size(); i++){
		if (s1[i] == s2[i])
			returnval++;
	}
	return returnval;
}