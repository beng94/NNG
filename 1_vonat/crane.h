#include <string>
#include <vector>
#include <iostream>

class Crane{

	std::string target, current;
	int doneupto;

public:

	Crane(std::string s1, std::string s2) : target(s2), current(s1), doneupto(0){}

	void sort();

	std::vector<int> findbestchange();

	std::string stringflip(std::string, int, int);

	void getresults(){
		std::cout << current << std::endl << target;
	}

	int matchingchars(std::string, std::string);
};