#include <vector>
#include <list>

class PrisonerGroup{

	std::vector<int> Members;

public:

	PrisonerGroup(){
		Members.reserve(1000);
	};

	bool addnumber(int);

	void printgroup();
};

class Prison{

	std::vector<PrisonerGroup> Groups;

public:

	Prison(){
		Groups.reserve(200);
		PrisonerGroup p1, p2, p3, p4, p5;
		Groups.push_back(p1);
		Groups.push_back(p2);
		Groups.push_back(p3);
		Groups.push_back(p4);
		Groups.push_back(p5);
	}

	void addnumber(int);

	void addnumberb(int);

	void printgroups();
};