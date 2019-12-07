#include <iostream>
#include <fstream>
#include <vector>

int						main(void)
{
	std::fstream		infile("InputPart1.txt");
	std::vector<int>	numbers;
	std::vector<int>	numbersTemp;
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
		for (int input1 = 0; input1 < 100; input1++)
		{
			for (int input2 = 0; input2 < 100; input2++)
			{
				numbersTemp = numbers;
				numbersTemp[1] = input1;
				numbersTemp[2] = input2;
				for (int i = 0; i < numbersTemp.size() - 4; i += 4)
				{
					operation = numbersTemp[i];
					paramIndex1 = numbersTemp[i + 1];
					paramIndex2 = numbersTemp[i + 2];
					solutionIndex = numbersTemp[i + 3];
					if (operation == 1)
					{
						numbersTemp[solutionIndex] = numbersTemp[paramIndex1] + numbersTemp[paramIndex2];
					}
					else if (operation == 2)
					{
						numbersTemp[solutionIndex] = numbersTemp[paramIndex1] * numbersTemp[paramIndex2];
					}
					else
					{
						break ;
					}
				}
				if (numbersTemp[0] == 19690720)
				{
					std::cout << "input1: " << input1 << ", input2: " << input2 << std::endl;
					return (0);
				}
			}
		}
	}
	else
	{
		std::cout << "File \'InputPart1.txt: not found" << std::endl;
	}
	return (0);
}
