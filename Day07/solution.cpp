#include <iostream>
#include <unistd.h>

int			something(int phaseSetting, int thrusterSignal)
{
	int		savedStdout;
	int		savedStdin;
	int		pipefd[2];
	int		pid;
	char	*args[] = { "intcodeComputer", "input.txt", nullptr };
	int		thing;

	savedStdin = dup(0);
	savedStdout = dup(1);
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		// Child
		dup2(pipefd[0], 0);
		dup2(pipefd[1], 1);
		execv("intcodeComputer", args);
	}
	else
	{
		// Parent
		dup2(pipefd[0], 0);
		dup2(pipefd[1], 1);
		std::cout << phaseSetting << std::endl;
		std::cout << thrusterSignal << std::endl;
		wait(NULL);
		std::cin >> thing;
		dup2(savedStdin, 0);
		dup2(savedStdout, 1);
		close(savedStdin);
		close(savedStdout);
	}
	return (thing);
}

int			main(void)
{
	int		temp;
	int		maxThrust = 0;

	for (int a = 0; a < 5; a++)
	{
		for (int b = 0; b < 5; b++)
		{
			if (b == a)
			{
				continue ;
			}
			for (int c = 0; c < 5; c++)
			{
				if (c == a || c == b)
				{
					continue ;
				}
				for (int d = 0; d < 5; d++)
				{
					if (d == a || d == b || d == c)
					{
						continue ;
					}
					for (int e = 0; e < 5; e++)
					{
						if (e == a || e == b || e == c || e == d)
						{
							continue ;
						}
						temp = something(a, 0);
						temp = something(b, temp);
						temp = something(c, temp);
						temp = something(d, temp);
						temp = something(e, temp);
						if (temp > maxThrust)
						{
							maxThrust = temp;
							std::cout << "New max: " << maxThrust << " -- ";
							std::cout << "Phase settings: " << a << ", " << b << ", " << c << ", " << d << ", " << e << std::endl;
						}
					}
				}
			}
		}
	}
	std::cout << "Max thrust: " << maxThrust << std::endl;
	return (0);
}
