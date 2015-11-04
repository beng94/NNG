#include "crane.h"


void Crane::sort(){
	std::vector<int> changepair;
	while (doneupto != current.size()){
		changepair = findbestchange();
		current = stringflip(current, changepair[0], changepair[1]); //Flips the working string
		doneupto += changepair[1] - changepair[0]; //The amount of characters we flipped, the string is done up to this point
		std::cout << current << std::endl;
	}
}

std::string Crane::stringflip(std::string string, int b, int e){
	std::vector<std::string> substrings;
	std::string substring = string.substr(0, b);
	substrings.push_back(substring);
	substring = string.substr(b + 1, e);
	substrings.push_back(substring);
	substring = string.substr(e + 1, string.size());
	substrings.push_back(substring); //We create the 3 substrings, the part before the flip, the flipped part and the end
	substrings[1] = std::string(substrings[1].rbegin(), substrings[1].rend()); //We flip the middle part
	return substrings[0] + substrings[1] + substrings[2];
}

std::vector<int> Crane::findbestchange(){
	std::vector<int> returnval;
	int maxindex = 0, firstval;
	for (int i = doneupto+1; i < current.size(); i++){ //A simple maximum find based on the amount of matching chars if we flip
		std::string string = stringflip(current, doneupto, i); //The given segment (doneupto, i)
		int matching = matchingchars(string, target);
		if (matching > maxindex){
			maxindex = matching;
			firstval = i;
		}
	}
	returnval.push_back(doneupto);
	returnval.push_back(firstval);
	return returnval;
}

int Crane::matchingchars(std::string s1, std::string s2){
	int returnval = 0;
	for (int i = 0; i < s1.size(); i++){
		if (s1[i] == s2[i])
			returnval++;
	}
	return returnval;
}