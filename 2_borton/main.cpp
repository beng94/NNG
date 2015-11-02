#include "Prison.h"

void main(){
	Prison p;
	for (int i = 1; i < 51; i++)
		p.addnumber(i);
	p.printgroups();
	getchar();

}