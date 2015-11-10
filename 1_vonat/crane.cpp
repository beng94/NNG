#include "crane.h"
#include <utility>

void Crane::sort(){

	while (begin != end){
		std::vector<std::pair<int, int>> changepairs;
		changepairs.push_back(findbestchange_front());
		changepairs.push_back(findbestchange_back());
		changepairs.push_back(findbestchange_full());
		if (changepairs[0].first > changepairs[1].first &&
			changepairs[0].first > (changepairs[2].first + changepairs[2].second)){
			current = stringflip(current, begin, changepairs[0].second);
			begin += changepairs[0].first;
		}
		else if (changepairs[1].first > changepairs[0].first &&
			changepairs[1].first > (changepairs[2].first + changepairs[2].second)){
			current = stringflip(current, end - changepairs[1].second, end);
			end -= changepairs[1].first;
		}
		else{
			current = stringflip(current, begin, end);
			begin += changepairs[2].first;
			end -= changepairs[2].second;
		}
		std::cout << current << std::endl;
		getchar();
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
	int maxamount = 0, maxplace;
	for (int i = begin; i <= end; i++){
		int j = i;
		int k = begin;
		while (target[k] == current[j]){
			j--;
			k++;
			if ((k == end + 1) || (j == begin - 1))
				break;
		}
		if (k - begin > maxamount){
			maxamount = k - begin;
			maxplace = i;
		}
	}
	return std::pair<int, int>(maxamount, maxplace);
}

std::pair<int, int> Crane::findbestchange_back(){
	int maxamount = 0, maxplace;
	for (int i = end; i >= begin; i--){
		int j = i;
		int k = end;
		while (target[k] == current[j]){
			k--;
			j++;
			if ((k == begin - 1) || (j == end + 1))
				break;
		}
		if ((end - k) > maxamount){
			maxamount = end - k;
			maxplace = i;
		}
	}
	return std::pair<int, int>(maxamount, maxplace);
}

std::pair<int, int> Crane::findbestchange_full(){
	int goodfromfront = 0, goodfromback = 0, i = begin, j = end;
	while (target[i] == current[j]){
		goodfromfront++;
		i++;
		j--;
		if (i == end + 1 || j == begin - 1)
			break;
	}
	if (i != end + 1 && j != begin - 1){
		i = begin;
		j = end;
		while (target[j] == current[i]){
			goodfromback++;
			i++;
			j--;
			if (i == end + 1 || j == begin - 1)
				break;
		}
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