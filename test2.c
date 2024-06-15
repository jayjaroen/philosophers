// condition variable in c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutexFuel;
int fuel = 0;

void *fuel_filling()
{
	printf("Ffilling fuel\n");
}

void *car(void *arg)
{
	printf("here to get fuel\n");
}

int	main(int argc, char **argv)
{
	pthread_t th[2];
	int	i;

	pthread_mutex_init(&mutexFuel, NULL);
	i = 0;
	while (i < 2)
	{
		if (i == 1)
		{
			if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
				perror("Failed to create thread\n");
		}
		else
		{
			if (pthread_creat(&th[i], NULL, &car, NULL) != 0)
				perror("Failed to create thread\n");
		}
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread\n");
		}
		i++;
	}
	pthread_mutex_destroy(&mutexFuel);
	return (0);
}
