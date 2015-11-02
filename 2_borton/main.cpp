#include "Prison.h"
#include <iostream>

void main(){
	Prison p;
	for (int i = 1; i < 501; i++){
		p.addnumberb(i);
		p.addnumberb(i);
		std::cout << i << std::endl;
	}
	p.printgroups();
	getchar();

}