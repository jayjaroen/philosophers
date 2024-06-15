#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
//////////////////// Differences between threads && processes ////////
/// see the run time ./(program)
// Thread Having access to the same variable
/// Deadlock condition -> data race (Valgrind ,Helgrind)
// valgrind --tool=helgrind ./philo --> checking threads, data races


typedef struct s_struct
{
	long	*add;
	int		x;
	int		mail;
	int		lock;
	pthread_mutex_t	mutex;
} t_struct;

//////////////////////////////////Racing Condition/////////////////////////////////
// void* routine(void *args)
// {
// 	t_struct *argument = (t_struct *)args;
// 	for (int i = 0; i < 1000000; i++)
// 	{
// 		pthread_mutex_lock(&argument->mutex); // lock
// 		argument->mail++;
// 		pthread_mutex_unlock(&argument->mutex); //unlock
// 	} 
// 	return (NULL);
// 		// read the value in mails
// 		// increment the value of mails
// }
// // solving the thread issue -> MUTEX
// int	main(void)
// {

// 	///////////////////////////////////////////////////////////
// 	///// Looping to create pthread_create && pthread_join
// 	pthread_t	t1; // two threads in the process
// 	pthread_t	t2;

// 	t_struct args;

// 	args.mail = 0;
// 	args.lock = 0;
// 	pthread_mutex_init(&args.mutex, NULL);
// 	if (pthread_create(&t1, NULL,&routine, &args))
// 		return (1);
// 	if (pthread_create(&t2, NULL,&routine, &args))
// 		return (1);
// 	if (pthread_join(t1, NULL))
// 		return (1);
// 	if (pthread_join(t2, NULL))
// 		return (1);
// 	pthread_mutex_destroy(&args.mutex);
// 	printf("Number of Mail: %d\n", args.mail);
// 	return (0);
// }
/////////////////////////////////////////Difference between trylock and lock in C///////////////////////
pthread_mutex_t mutex;

void *routine(void* (arg))
{
	if (pthread_mutex_trylock(&mutex) == 0) // no guarantee that you will get lock differnce from lock
	{
		printf("Got lock\n");
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
	else
	{
		printf("no lock\n");
	}
	return (NULL);
}


int main(void)
{
	pthread_t th[4];
	int i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < 4)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Error\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Error\n");
			return (1);
		}
		i++;
	}
	pthread_mutex_destroy(&mutex);
}
//////////////////////////////////////////Pass agrument in a thread ////////////////////////////////////
/// solution: memory allocation

// int	prime[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

// void *routine(void *arg)
// {
// 	int index = *(int *)arg; // typecast void pointer
// 	int sum = 0;
// 	int j = 0;

// 	while (j < 5)
// 	{
// 		sum += prime[index + j];
// 		j++;
// 	}
// 	printf("Local sum: %d\n", sum);
// 	*(int*)arg = sum;
// 	// printf("%d\n", prime[index]);
// 	// printf("%d\n", index);
// 	// free(arg);
// 	return arg;
// }

// int main(void)
// {
// 	pthread_t th[2];
// 	int i;
// 	int globalsum;

// 	i = 0;
// 	while (i < 2)
// 	{
// 		int *a = malloc(sizeof(int));
// 		*a = i * 5; // 0 && 5 (Sum of all 10 prime number)
// 		if (pthread_create(&th[i], NULL, &routine, a) != 0)
// 		{
// 			perror("Error in pthread create\n");
// 			return (1);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	globalsum = 0;
// 	while (i < 2)
// 	{
// 		int *a;
// 		if (pthread_join(th[i], (void **)&a) != 0)
// 		{
// 			perror("Error in pthread join\n");
// 			return (1);
// 		}
// 		globalsum += *a;
// 		free(a);
// 		i++;
// 	}
// 	printf("Global Sum is %d\n", globalsum);
// 	return (0);
// }

/////////////////////////////////////pthread_join/////////////////////////////////////////////////////////
// void *roll_dice()
// {
// 	int value = (rand() % 6) + 1;
// 	int	*result = malloc(sizeof(int));
	
// 	*result = value;
// 	printf("the result is: %p\n", result); // same address as in the main
// 	return (void *)result;
// }

// int	main(void)
// {
// 	int	*res;
// 	srand(time(NULL)); // check this
// 	pthread_t th;
// 	// printf("Address: %p\n", &res);
// 	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
// 		return (1);
// 	if (pthread_join(th, (void **)&res)!= 0)
// 		return 1;
// 	printf("Result: %d, %p\n", *res, res); //same address as in the roll dice function
// 	free(res);
// }

// /////////////////////////////////////Before/////////////////////////////////////////////////////////
// void*	routine(void *args)
// {
// 	t_struct *argument = (t_struct *)(args);
// 	long *add_num = argument->add;
// 	argument->x++;
// 	printf("Hi Hi, add: %ld\n", *add_num);
// 	printf("Process id: %d\n", getpid());
// 	printf("Value of x: %d\n", argument->x);
// 	sleep(3);
// 	printf("ending thread\n");
// 	return (NULL); // why need to return a void pointer
// }

// void*	routine2(void *args)
// {
// 	t_struct *argument = (t_struct *)(args);
// 	printf("Value of x: %d\n", argument->x);
// 	return (NULL);
// }

// int	main(int agrc, char **argv)
// {
// 	pthread_t	t1;
// 	pthread_t	t2;
// 	int	x;
// 	long value1 = 1;
// 	long value2 = 2;
// 	x = 2;
// 	t_struct args;
// 	args.x = 2;
// 	args.add = &value1;

// 	if (pthread_create(&t1, NULL, &routine, &args) != 0)
// 		return (1);
// 	if (pthread_create(&t2, NULL, &routine2, &args) != 0)
// 		return (1);
// 	if (pthread_join(t1, NULL) != 0) //wait for thread
// 		return (1);
// 	if (pthread_join(t2, NULL) != 0)
// 		return (1);
// 	return 0;
// }