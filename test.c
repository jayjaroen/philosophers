#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
//////////////////// Differences between threads && processes ////////
/// see the run time ./(program)
// Thread Having access to the same variable
typedef struct s_struct
{
	long	*add;
	int		x;
	int		mail;
	int		lock;
	pthread_mutex_t	mutex;
} t_struct;

/////////////////////Racing Condition/////////////////////////////////
void* routine(void *args)
{
	t_struct *argument = (t_struct *)args;
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&argument->mutex); // lock
		argument->mail++;
		pthread_mutex_unlock(&argument->mutex); //unlock
	} 
	return (NULL);
		// read the value in mails
		// increment the value of mails
}
// solving the thread issue -> MUTEX
int	main(int argc, char **argv)
{
	pthread_t t[atoi(argv[1])];
	while ()
	/////////////////////////////////////////////////////////////
	// pthread_t	t1;
	// pthread_t	t2;

	// t_struct args;

	// args.mail = 0;
	// args.lock = 0;
	// pthread_mutex_init(&args.mutex, NULL);
	// if (pthread_create(&t1, NULL,&routine, &args))
	// 	return (1);
	// if (pthread_create(&t2, NULL,&routine, &args))
	// 	return (1);
	// if (pthread_join(t1, NULL))
	// 	return (1);
	// if (pthread_join(t2, NULL))
	// 	return (1);
	// pthread_mutex_destroy(&args.mutex);
	// printf("Number of Mail: %d\n", args.mail);
	// return (0);
}
//////////////////////////////////////////////////////////////////////
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