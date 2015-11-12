#include "crane.h"
#include <iostream>

int main(){
	//Pájnusz monochrome perpetuity
	Crane c("hcedffhcjjhgbgjiiadg", "jhhhgbcjffdecgjgdaii");
	std::cout << c.stringflip("aaabbbccc", 1, 3) << std::endl;
	c.sort();
	c.getresults();
	std::string valami("abcdefgh");
	std::cout << std::endl << std::string(valami.rbegin(), valami.rend()) << std::endl;
	std::cout << valami.substr(2, 4) << std::endl;
	std::cout << c.stringflip(valami, 2, 6);
	getchar();
	while (true){}
}