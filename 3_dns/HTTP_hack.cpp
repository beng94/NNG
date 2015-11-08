
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <tchar.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

using namespace std;

int main()
{
	const TCHAR url[] = _T("http://ge.tt/api/1/files/77h0hRR2/0/blob?download");
	const TCHAR location[] = _T("dns.txt");

	HRESULT hr = URLDownloadToFile(NULL, url, location, 0, NULL);

	std::ifstream file("dns.txt");
	std::string dns;

	file >> dns;
	std::cout << dns << std::endl;
	file.close();
}