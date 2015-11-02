#include "Prison.h"
#include <iostream>

bool PrisonerGroup::addnumber(int prisonerID){
	if (Members.size() != 0){
		for (int i = 0; i < Members.size() - 1; i++){
			for (int j = i + 1; j < Members.size(); j++){
				int a = Members[i];
				int b = Members[j];
				if (a + b == prisonerID || a + prisonerID == b || b + prisonerID == a){
					return false;
				}
			}
		}
	}
	Members.push_back(prisonerID);
	return true;
}

void PrisonerGroup::printgroup(){
	for (int i = 0; i < Members.size(); i++){
		std::cout << Members[i] << ' ';
	}
}

void Prison::addnumber(int prisonerID){
	if (Groups.size() != 0){
		for (int i = 0; i < Groups.size(); i++){
			if (Groups[i].addnumber(prisonerID)){
				return;
			}
		}
	}
	PrisonerGroup pg;
	pg.addnumber(prisonerID);
	Groups.push_back(pg);
//	addnumber(prisonerID);
}

void Prison::addnumberb(int prisonerID){
	if (prisonerID % 2)
		Groups[0].addnumber(prisonerID);
	else if (prisonerID % 6 == 2)
		Groups[1].addnumber(prisonerID);
	else if (prisonerID % 6 == 4)
		Groups[2].addnumber(prisonerID);
	else if (prisonerID % 9 == 3)
		Groups[3].addnumber(prisonerID);
	else if (prisonerID % 9 == 6)
		Groups[4].addnumber(prisonerID);
	else
		addnumber(prisonerID);
}

void Prison::printgroups(){
	std::cout << Groups.size() << std::endl;
	for (int i = 0; i < Groups.size(); i++){
		std::cout << i << ". group: ";
		Groups[i].printgroup();
		std::cout << std::endl;
	}
}
