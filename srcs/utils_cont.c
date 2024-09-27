/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cont.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:05:12 by jjaroens          #+#    #+#             */
/*   Updated: 2024/09/25 14:51:56 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
//thread handler// CREATE/ INIT/ JOIN/ DETACH
void	thread_error_handler(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (status == EAGAIN)
		exit_error("The system lacked the necessary resources to \
		create another thread");
	else if (status == EPERM)
		exit_error("The caller does not have appropriate permission");
	else if (status == EINVAL && opcode == CREATE)
		exit_error("The value specified by attr is invalid.");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		exit_error("the value specified by thread does not refer \
		to a joinable thread");
	else if (status == ESRCH)
		exit_error("No thread could be found");
	else if (status == EDEADLK)
		exit_error("A deadlock was detected");
} 

void    thread_handler(pthread_t *th, void * (*foo)(void *), void *data, 
    t_opcode opcode)
{
    if (opcode == CREATE)
        thread_error_handler(pthread_create(th, NULL, foo, data), opcode);
    else if (opcode == JOIN)
        thread_error_handler(pthread_join(*th, NULL), opcode);
    else if (opcode == DETACH)
        thread_error_handler(pthread_detach(*th), opcode);
    else
        exit_error("Wrong opcode for thread");
}

long	ft_gettime(void)
{
	// To return in milliseconds
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		exit_error("Failed to get time");
	return ((tv.tv_sec * 1e3) + (tv.tv_usec/ 1e3));
}

void	write_status(t_philo *philo, t_philo_status status)
{
	long	elapsed_time;
	// should also use this to update in the data struct?
	// the time should take less than allowed time - put it in the function
	// of each activtiy
	elapsed_time = ft_gettime() - philo->data->start_simulation;
	// if (philo->is_full || simulation_finished(philo->data))
		// TODO
	// 	return ;
	mutex_handler(&philo->write_mutex, LOCK);
	if (status == TAKE_FIRST_FORK)
		printf(GREEN "%-5ld" CYAN "Philo no. %d has picked up a first fork" 
		RESET "\n", elapsed_time, philo->id);
	else if (status == TAKE_SECOND_FORK)
		printf(GREEN "%-5ld" CYAN "Philo no. %d has picked up a second fork"
		RESET "\n",elapsed_time, philo->id);
	else if (status == EAT)
		printf(GREEN "%-5ld" CYAN "Philo no. %d starts eating" RESET "\n",
		elapsed_time, philo->id);
	else if (status == SLEEP)
		printf(GREEN "%-5ld" CYAN "Philo no. %d is sleeping" RESET "\n",
		elapsed_time, philo->id);
	else if (status == THINK)
		printf(GREEN "%-5ld" CYAN "Philo no. %d is thinking" RESET "\n",
		elapsed_time, philo->id);
	mutex_handler(&philo->write_mutex, UNLOCK);
}

void	ft_usleep(long consumed_time)
{
	long	start;
	long	elapsed_time;
	long	remaining_time;
	
	start = ft_gettime();// result in milliseconds
	while (ft_gettime() - start < consumed_time)
	{
		//check - get_bool function condition and break
		// end_time is true then should get out of the loop
		// the condition to break out the loop: 1) The time is over; 2) the end
		// time is up (simulation end time?)
		elapsed_time = ft_gettime() - start;
		remaining_time = consumed_time - elapsed_time;
		if (remaining_time > 1e7) // 10,000 microseconds
			usleep(remaining_time/2);
	}
}