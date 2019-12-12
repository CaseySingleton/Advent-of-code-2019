#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

typedef std::map<std::string, std::vector<std::string> > orbitalMap;
typedef orbitalMap::iterator orbitalMapIterator;

orbitalMap				plotOrbits(char *fileName)
{
	std::fstream		infile(fileName);
	std::string			line;
	std::string			left;
	std::string			right;
	orbitalMap 			orbits;
	int					pos;

	if (infile)
	{
		while (std::getline(infile, line))
		{
			pos = line.find(")");
			left = line.substr(0, pos);
			right = line.substr(pos + 1);
			orbits[left].push_back(right);
		}
	}
	else
	{
		std::cout << "File: " << fileName << ": Unable to find or open" << std::endl;
	}
	return (orbits);
}

int						countOrbits(orbitalMap & orbits, std::string key, int depth)
{
	int					temp;

	temp = 0;
	for (int i = 0; i < orbits[key].size(); i++)
	{
		temp += countOrbits(orbits, orbits[key].at(i), depth + 1);
	}
	return (depth + temp);
}

void					shortestDistanceHelper(orbitalMap & orbits, std::string key, std::map<std::string, int> & info, std::string d1, std::string d2)
{
	if (key == d1 || key == d2)
	{
		info["finished"] += 1;
	}
	if (info["finished"] == 1)
	{
		info["transfers"] += 1;
		info[key] = 1;
	}
	for (int i = 0; i < orbits[key].size(); i++)
	{
		shortestDistanceHelper(orbits, orbits[key].at(i), info, d1, d2);
	}
	if (info["finished"] == 1)
	{
		if (info[key] == 1)
		{
			info["transfers"] -= 1;
		}
		else
		{
			info["transfers"] += 1;
			info[key] = 1;
		}
	}	
}

int						shortestDistance(orbitalMap & orbits, std::string start, std::string destination1, std::string destination2)
{
	std::map<std::string, int>	info;

	info["finished"] = 0;
	info["transfers"] = 0;
	shortestDistanceHelper(orbits, start, info, destination1, destination2);
	return (info["transfers"]);
}

int						main(int argc, char *argv[])
{
	orbitalMap			orbits;
	std::string			key;

	if (argc == 2)
	{
		orbits = plotOrbits(argv[1]);
		std::cout << "Number of orbits: " << countOrbits(orbits, "COM", 0) << std::endl;
		std::cout << "Number of transfers: " << shortestDistance(orbits, "COM", "YOU", "SAN") << std::endl;
	}
	else
	{
		std::cout << "Usage: a.out \'fileName\'" << std::endl;
	}
	return (0);
}
