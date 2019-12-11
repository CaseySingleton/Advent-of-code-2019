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

int						printOrbits(orbitalMap & orbits, std::string key, int depth)
{
	int					temp = 0;

	for (int i = 0; i < orbits[key].size(); i++)
	{
		temp += printOrbits(orbits, orbits[key].at(i), depth + 1);
	}
	return (depth + temp);
}

int						main(int argc, char *argv[])
{
	orbitalMap			orbits;
	std::string			key;
	int					numberOfOrbits;

	numberOfOrbits = 0;
	if (argc == 2)
	{
		orbits = plotOrbits(argv[1]);
		std::cout << "The number of direct and indirect orbits is: " << printOrbits(orbits, "COM", 0) << std::endl;;
	}
	else
	{
		std::cout << "Usage: a.out \'fileName\'" << std::endl;
	}
	return (0);
}
