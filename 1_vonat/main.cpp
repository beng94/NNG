#include "crane.h"
#include <iostream>

int main(){
	//Pájnusz monochrome perpetuity
	Crane c("aaabbbccc", "aababbccc");
	c.sort();
	c.getresults();
	std::string valami("faabbccaa");
	std::cout << std::endl << std::string(valami.rbegin(), valami.rend()) << std::endl;
	std::cout << valami.substr(2, 6) << std::endl;
	std::cout << c.stringflip(valami, 2, valami.size());
	getchar();
	while (true){}
}