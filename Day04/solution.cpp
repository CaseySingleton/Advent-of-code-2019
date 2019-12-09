#include <iostream>
#include <string>

int				isValidPassword(int n)
{
	int			hasDouble;
	int			howManyDoubles;
	int			right;
	int			left;

	hasDouble = 0;
	howManyDoubles = 0;
	while (n > 10)
	{
		right = n % 10;
		n /= 10;
		left = n % 10;
		if (left > right)
		{
			return (0);
		}
		else if (left == right)
		{
			howManyDoubles += 1;
		}
		else if (howManyDoubles == 1)
		{
			hasDouble = 1;
			howManyDoubles = 0;
		}
		else
		{
			howManyDoubles = 0;
		}
	}
	return ((hasDouble == 1 || howManyDoubles == 1));
}

int				main(void)
{
	int			start;
	int			stop;
	int			possibleSolutions;

	start = 357253;
	stop = 892942;
	possibleSolutions = 0;
	while (start <= stop)
	{
		possibleSolutions += isValidPassword(start);
		start += 1;
	}
	std::cout << "Possible passwords: " << possibleSolutions << std::endl;
	return (0);
}
