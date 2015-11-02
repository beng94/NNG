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
	}

	void addnumber(int);

	void printgroups();
};