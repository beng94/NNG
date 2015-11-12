#include <string>
#include <vector>
#include <iostream>
#include <utility>

class Crane{

	std::string target, current;
	int begin, end;
	std::vector<std::pair<int, int>> moves;

public:

	Crane(std::string s1, std::string s2) : target(s2), current(s1), begin(0), end(s2.size()-1){
		while (current[begin] == target[begin])
			begin++;
		while (current[end] == target[end])
			end--;
	}

	void sort();

	std::pair<int, int> findbestchange_front();

	std::pair<int, int> findbestchange_back();

	std::pair<int, int> findbestchange_full();

	std::string stringflip(std::string, int, int);

	void getresults(){
		std::cout << moves.size() << std::endl;
		for (int i = 0; i < moves.size(); i++){
			std::cout << moves[i].first << ' ' << moves[i].second << std::endl;
		}
	}

	int matchingchars(std::string, std::string);
};