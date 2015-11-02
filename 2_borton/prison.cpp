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
	Groups.push_back(pg);
	addnumber(prisonerID);
}

void Prison::printgroups(){
	std::cout << Groups.size() << std::endl;
	for (int i = 0; i < Groups.size(); i++){
		Groups[i].printgroup();
		std::cout << std::endl;
	}
}
