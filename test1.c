#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

// Child process && main process

int	main(void)
{
	int id = fork();
	int n;
	int x = 0;
	
	if (id == 0)
	{
		// printf("Hello from a child process\n");
		n = 1;
	}
	else
	{
		// printf("Hello from a main process\n");
		n = 6;
	}
	// fork(); // 2^n
	// fork();
	// if (id != 0)
		// wait(); // inside arg?
	if (id == 0)
		x++;
	printf("x value:%d\n", x);
	printf("Process id: %d\n", getpid());
	for (int i = n; i < n + 5; i++)
	{
		if (id == 0)
			printf("this is a child process");
		else
			printf("this is a main process");
		printf("%d", i);
		fflush(stdout);
	}
	printf("\n");
	return (0);
}