#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct					Point
{
	int					x;
	int					y;
};

struct					Line
{
	Point				p1;
	Point				p2;
};

int						distanceFromOrigin(Point point)
{
	return (abs(point.x) + abs(point.y));
}

int						distanceFromOrigin(int x, int y)
{
	return (abs(x) + abs(y));
}

std::vector<Line>		parse(std::string str)
{
	std::istringstream	ss(str);
	std::string			delimiter;
	std::string			token;
	std::vector<Line>	tokens;
	Line				line = (Line){ (Point){ 0, 0 }, (Point){ 0, 0 } };
	int					pos;

	delimiter = ",";
	do
	{
		pos = str.find(delimiter);
		token = str.substr(0, pos);
		if (str[0] == 'U')
		{
			line.p2.y += std::stoi(token.substr(1));
		}
		else if (str[0] == 'D')
		{
			line.p2.y -= std::stoi(token.substr(1));
		}
		else if (str[0] == 'L')
		{
			line.p2.x -= std::stoi(token.substr(1));
		}
		else if (str[0] == 'R')
		{
			line.p2.x += std::stoi(token.substr(1));
		}
		str.erase(0, pos + delimiter.length());
		tokens.push_back(line);
		line.p1 = line.p2;
	} while (pos != std::string::npos);
	return (tokens);
}

bool					isBetween(int a, int b, int c)
{
	return (a > std::min(b, c) && a < std::max(b, c));
}

bool					linesIntersect(Line l1, Line l2)
{
	if (l1.p1.x == l1.p2.x && l2.p1.y == l2.p2.y)
	{
		if (isBetween(l1.p1.x, l2.p1.x, l2.p2.x) && isBetween(l1.p2.x, l2.p1.x, l2.p2.x) && isBetween(l2.p1.y, l1.p1.y, l1.p2.y) && isBetween(l2.p2.y, l1.p1.y, l1.p2.y))
		{
			return (true);
		}
	}
	else if (l1.p1.y == l1.p2.y && l2.p1.x == l2.p2.x)
	{
		if (isBetween(l1.p1.y, l2.p1.y, l2.p2.y) && isBetween(l1.p2.y, l2.p1.y, l2.p2.y) && isBetween(l2.p1.x, l1.p1.x, l1.p2.x) && isBetween(l2.p2.x, l1.p1.x, l1.p2.x))
		{
			return (true);
		}
	}
	return (false);

}

Point					findIntersection(Line l1, Line l2)
{
	if (l1.p1.x == l1.p2.x)
	{
		return (Point){ l1.p1.x, l2.p1.y };
	}
	else
	{
		return (Point){ l2.p1.x, l1.p1.y };
	}
}

int						stepsFromPointAToPointB(Point a, Point b)
{
	return (abs(a.x - b.x) + abs(a.y - b.y));
}

int						main(void)
{
	std::fstream		infile("InputPart1.txt");
	std::string			lineFromFile1;
	std::string			lineFromFile2;
	std::vector<Line>	wire1;
	std::vector<Line>	wire2;
	Point				intersection;
	Point				closest;
	Point				lowestSteps;
	int					wire1Steps;
	int					wire2Steps;
	int					smallestSteps;
	bool				first;

	wire1Steps = 0;
	wire2Steps = 0;
	first = true;
	getline(infile, lineFromFile1);
	getline(infile, lineFromFile2);
	wire1 = parse(lineFromFile1);
	wire2 = parse(lineFromFile2);
	for (std::vector<Line>::iterator it1 = wire1.begin(); it1 != wire1.end(); it1++)
	{
		wire2Steps = 0;
		for (std::vector<Line>::iterator it2 = wire2.begin(); it2 != wire2.end(); it2++)
		{
			// std::cout << "Wire 1 steps: " << wire1Steps << ", wire 2 steps: " << wire2Steps << std::endl;
			if (linesIntersect(*it1, *it2))
			{
				intersection = findIntersection(*it1, *it2);
				if (first == true || distanceFromOrigin(intersection) < distanceFromOrigin(closest))
				{
					closest = intersection;
				}
				if (first == true || wire2Steps + stepsFromPointAToPointB(it2->p1, intersection) + wire1Steps + stepsFromPointAToPointB(it1->p1, intersection) < smallestSteps)
				{
					smallestSteps = wire2Steps + stepsFromPointAToPointB(it2->p1, intersection) + wire1Steps + stepsFromPointAToPointB(it1->p1, intersection);
				}
				first = false;
			}
			wire2Steps += stepsFromPointAToPointB(it2->p1, it2->p2);
		}
		wire1Steps += stepsFromPointAToPointB(it1->p1, it1->p2);
	}
	std::cout << "Closest: (" << closest.x << ", " << closest.y << "), distance: " << distanceFromOrigin(closest) << std::endl;
	std::cout << "Smalles steps: " << smallestSteps << std::endl;
	return (0);
}
