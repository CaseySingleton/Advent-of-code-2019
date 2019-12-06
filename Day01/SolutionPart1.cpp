#include <iostream>
#include <fstream>

int					main(void)
{
	std::ifstream	infile("InputPart1.txt");
	std::string		line;
	int				sum;

	sum = 0;
	if (infile)
	{
		while (std::getline(infile, line))
		{
			sum += std::stoi(line) / 3 - 2;
		}
		std::cout << "The sum of the fuel requirements is: " << sum << std::endl;
	}
	else
	{
		std::cout << "File \'input\': not found" << std::endl;
	}
	return (0);
}
