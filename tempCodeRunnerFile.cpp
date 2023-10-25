#include "Restaurant.cpp"
#include <fstream>

void simulate(string filename, imp_res *r)
{
	ifstream ss(filename);
	string str, maxsize, name, energy, num;
	while (ss >> str)
	{
		if (str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize);
		}