#include <iostream>
#include <fstream>
#include <vector>

int						main(void)
{
	std::fstream		infile("InputPart1.txt");
	std::vector<int>	numbers;
	std::string			line;
	int					operation;
	int					paramIndex1;
	int					paramIndex2;
	int					solutionIndex;

	if (infile)
	{
		while (std::getline(infile, line, ','))
		{
			numbers.push_back(std::stoi(line));
		}
		numbers[1] = 12;
		numbers[2] = 2;
		for (int i = 0; i < numbers.size() - 4; i += 4)
		{
			operation = numbers[i];
			paramIndex1 = numbers[i + 1];
			paramIndex2 = numbers[i + 2];
			solutionIndex = numbers[i + 3];
			if (operation == 1)
			{
				numbers[solutionIndex] = numbers[paramIndex1] + numbers[paramIndex2];
			}
			else if (operation == 2)
			{
				numbers[solutionIndex] = numbers[paramIndex1] * numbers[paramIndex2];
			}
			else
			{
				break ;
			}
		}
		std::cout << "The value of position 0 is: " << numbers[0] << std::endl;
	}
	else
	{
		std::cout << "File \'InputPart1.txt: not found" << std::endl;
	}
	return (0);
}
