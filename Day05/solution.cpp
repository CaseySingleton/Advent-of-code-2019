#include <iostream>
#include <fstream>
#include <vector>

typedef int (optFunc)(std::vector<int> &, int);

std::vector<int>		getInstructions(std::string fileName)
{
	std::fstream		infile(fileName);
	std::vector<int>	instructions;
	std::string			line;

	if (infile)
	{
		while (std::getline(infile, line, ','))
		{
			instructions.push_back(std::stoi(line));
		}
	}
	else
	{
		std::cout << "File: " << fileName << ": Unable to find or open" << std::endl;
		exit(0);
	}
	return (instructions);
}

int						optcode1(std::vector<int> & instructions, int index)
{
	int					solutionIndex;
	int					mode1;
	int					mode2;
	int					param1;
	int					param2;

	solutionIndex = instructions[index + 3];
	mode1 = instructions[index] / 100 % 10;
	mode2 = instructions[index] / 1000;
	param1 = (mode1 == 1) ? instructions[index + 1] : instructions[instructions[index + 1]];
	param2 = (mode2 == 1) ? instructions[index + 2] : instructions[instructions[index + 2]];
	instructions[solutionIndex] = param1 + param2;
	return (4);
}

int						optcode2(std::vector<int> & instructions, int index)
{
	int					solutionIndex;
	int					mode1;
	int					mode2;
	int					param1;
	int					param2;

	solutionIndex = instructions[index + 3];
	mode1 = instructions[index] / 100 % 10;
	mode2 = instructions[index] / 1000;
	param1 = (mode1 == 1) ? instructions[index + 1] : instructions[instructions[index + 1]];
	param2 = (mode2 == 1) ? instructions[index + 2] : instructions[instructions[index + 2]];
	instructions[solutionIndex] = param1 * param2;
	return (4);
}


int						optcode3(std::vector<int> & instructions, int index)
{
	int					input;

	std::cout << "Enter an ID: ";
	std::cin >> input;
	instructions[instructions[index + 1]] = input;
	return (2);
}

int						optcode4(std::vector<int> & instructions, int index)
{
	int					mode;

	mode = instructions[index] / 100 % 10;
	std::cout << "Diagnostic code: ";
	std::cout << ((mode == 1) ? instructions[index + 1] : instructions[instructions[index + 1]]) << std::endl;
	return (2);
}

void					performInstructions(std::vector<int> & instructions)
{
	optFunc				*dispatch[4] = {
							optcode1,
							optcode2,
							optcode3,
							optcode4
	};
	int					operation;
	int					i;

	i = 0;
	while (i < instructions.size())
	{
		operation = instructions[i] % 10;
		if (operation > 4)
		{
			break ;
		}
		i += dispatch[operation - 1](instructions, i); 
	}
}

int						main(int argc, char *argv[])
{
	std::vector<int>	instructions;

	if (argc == 2)
	{
		instructions = getInstructions(argv[1]);
		performInstructions(instructions);
	}
	return (0);
}

