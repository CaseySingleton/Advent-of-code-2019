#include <iostream>
#include <fstream>

int					calculateFuelRequirement(int mass)
{
	int				fuel;

	fuel = mass / 3 - 2;
	if (fuel <= 0)
	{
		return (0);
	}
	return (fuel + calculateFuelRequirement(fuel));
}

int					main(void)
{
	std::ifstream	infile("InputPart2.txt");
	std::string		line;
	int				sum;

	sum = 0;
	if (infile)
	{
		while (std::getline(infile, line))
		{
			sum += calculateFuelRequirement(std::stoi(line));
		}
		std::cout << "The sum of the fuel requirements including the mass of the fuel is: " << sum << std::endl;
	}
	else
	{
		std::cout << "File \'input\': not found" << std::endl;
	}
	return (0);
}
