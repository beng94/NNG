#include "crane.h"
#include <utility>
#include <iostream>
#include <fstream>
#include <algorithm>

void Crane::sort(){
	//std::ofstream farok;
	//farok.open("valami2.txt", std::ios::app);
	islandsort(begin, end);
	std::cout << current << " " << target;
	/*std::cout << current << " " << target << std::endl;
	while (begin != end && begin < end){
		farok << current << " " << target << std::endl;
		std::vector<std::pair<int, int>> changepairs;
		changepairs.push_back(findbestchange_front(begin, end));
		changepairs.push_back(findbestchange_back(begin, end));
		//changepairs.push_back(findbestchange_full());

		if (changepairs[0].first > changepairs[1].first/* &&
			changepairs[0].first > (changepairs[2].first + changepairs[2].second)){

	/*		current = stringflip(current, begin, changepairs[0].second);
			farok << "eleje" << begin << ' '<< changepairs[0].second << std::endl;
			moves.push_back(std::pair<int, int>(begin, changepairs[0].second));
			begin += changepairs[0].first;
		}

		else if (changepairs[1].first >= changepairs[0].first/* &&
			changepairs[1].first > (changepairs[2].first + changepairs[2].second)){

			/*current = stringflip(current,changepairs[1].second, end);
			farok << "vege" << changepairs[1].second << ' ' << end << std::endl;
			moves.push_back(std::pair<int, int>(changepairs[1].second, end));
			end -= changepairs[1].first;
		}

		else{
			current = stringflip(current, begin, end);
			farok << "egesz" << begin << ' ' << end << std::endl;
			moves.push_back(std::pair<int, int>(begin, end));
			begin += changepairs[2].first;
			end -= changepairs[2].second;
		}
	}
	farok << current << " " << target << std::endl;
	farok.close();*/
}

void Crane::islandsort(int from, int to){
	
	if (from >= to){
		return;
	}

	int max = 0;
	std::pair<int, int> flip;
	std::pair<int, int> gotinplace;

	auto fasz = findbestchange_front(from, to);
	max = fasz.first;
	flip = std::pair<int, int>(from, fasz.second);
	gotinplace = std::pair<int, int>(from + max, to);

	fasz = findbestchange_back(from, to);
	if (fasz.first >= max){
		max = fasz.first;
		flip = std::pair<int, int>(fasz.second, to);
		gotinplace = std::pair<int, int>(from, to-fasz.first);
	}

	fasz = findbestchange_full(from, to);
	if ((fasz.first + fasz.second) >= max){
		max = fasz.first;
		flip = std::pair<int, int>(from, to);
		gotinplace = std::pair<int, int>(from + fasz.first, to - fasz.second);
	}

	std::pair<int, int> islandat(-1, -1);

	for (int i = from; i < to - 1; i++){
		std::cout << i << std::endl;
		for (int j = i + 1; j < to; j++){
			auto farok = findisland(current.substr(from, to - from), i - from, j - from, from, to);
			if (farok[0] >= max){
				max = farok[0];
				flip = std::pair<int, int>(i, j);
				islandat = std::pair<int, int>(farok[1], farok[2]);
			}
		}
	}

	current = stringflip(current, flip.first, flip.second);
	moves.push_back(std::pair<int, int>(flip.first, flip.second));

	if (islandat.first != -1){
		islandsort(from, islandat.first);
		islandsort(islandat.second, to);
	}
	else{
		islandsort(gotinplace.first, gotinplace.second);
	}
}

std::vector<int> Crane::findisland(std::string string, int startat, int endat, int globalstart, int globalend){

	string = stringflip(string, startat, endat);
	std::vector<int> returnval = { -1, 0, 0, };

	for (int i = startat; i < endat; i++){
		int islandlength = 0;
		int islandstart = i;
		while (string[i] == target[globalstart + i]){
			islandlength++;
			i++;
			if (i > endat)
				break;
		}
		if (islandisvalid(string, islandstart, globalstart)){
			if (islandlength > returnval[0]){
				returnval[0] = islandlength;
				returnval[1] = islandstart + globalstart;
				returnval[2] = returnval[1] + returnval[0];
			}
		}
	}
	return returnval;
}

bool Crane::islandisvalid(std::string string, int islandstart, int globalstart){

	std::string stringfasz2 = string.substr(0, islandstart);
	std::sort(stringfasz2.begin(), stringfasz2.end());

	std::string stringpina2 = target.substr(globalstart, islandstart);
	std::sort(stringpina2.begin(), stringpina2.end());

	if (stringfasz2 == stringpina2)
		return true;
	return false;
}

std::string Crane::stringflip(std::string string, int b, int e){
	std::vector<std::string> substrings;
	std::string substring = string.substr(0, b);
	substrings.push_back(substring);
	substring = string.substr(b, e - b + 1);
	substring = std::string(substring.rbegin(), substring.rend());
	substrings.push_back(substring);
	substring = string.substr(e + 1);
	substrings.push_back(substring); //We create the 3 substrings, the part before the flip, the flipped part and the end
	return substrings[0] + substrings[1] + substrings[2];
}

std::pair<int, int> Crane::findbestchange_front(int a, int b){
	int maxamount = 0, maxplace;
	for (int i = a; i <= b; i++){
		int j = i;
		int k = a;
		while (target[k] == current[j]){
			j--;
			k++;
			if ((k == b + 1) || (j == a - 1))
				break;
		}
		if ((k - a) > maxamount){
			maxamount = k - a;
			maxplace = i;
		}
	}
	return std::pair<int, int>(maxamount, maxplace);
}

std::pair<int, int> Crane::findbestchange_back(int a, int b){
	int maxamount = 0, maxplace;
	for (int i = b; i >= a; i--){
		int j = i;
		int k = b;
		while (target[k] == current[j]){
			k--;
			j++;
			if ((k == a - 1) || (j == b + 1))
				break;
		}
		if ((b - k) > maxamount){
			maxamount = b - k;
			maxplace = i;
		}
	}
	return std::pair<int, int>(maxamount, maxplace);
}

std::pair<int, int> Crane::findbestchange_full(int a, int b){
	int goodfromfront = 0, goodfromback = 0, i = a, j = b;

	while (target[i] == current[j]){
		goodfromfront++;
		i++;
		j--;
		if (i == b + 1 || j == a - 1)
			break;
	}
	i = a;
	j = b;
	while (target[j] == current[i]){
		goodfromback++;
		i++;
		j--;
		if (i == b + 1 || j == a - 1)
			break;
	}
	return std::pair<int, int>(goodfromfront, goodfromback);

}

int Crane::matchingchars(std::string s1, std::string s2){
	int returnval = 0;
	for (int i = 0; i < s1.size(); i++){
		if (s1[i] == s2[i])
			returnval++;
	}
	return returnval;
}