#include "crane.h"
#include <iostream>

int main(){
	//Pájnusz monochrome perpetuity
	Crane c("aaabbbccc", "abcabcabc");
	//c.sort();
	//c.getresults();
	std::string valami("aabbccaa");
	std::cout << std::string(valami.rbegin(), valami.rend()) << std::endl;
	std::cout << valami.substr(2, 6) << std::endl;
	std::cout << c.stringflip(valami, 2, valami.size());
	getchar();
}