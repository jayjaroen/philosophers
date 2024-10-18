/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cont.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:05:12 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/18 22:24:27 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_thread_error(int status, t_opcode opcode)
{
	if (status == EAGAIN)
		printf(RED "The system lacked the necessary resources to \
		create another thread");
	else if (status == EPERM)
		printf(RED "The caller does not have appropriate permission");
	else if (status == EINVAL && opcode == CREATE)
		printf(RED "The value specified by attr is invalid.");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		printf(RED "the value specified by thread does not refer \
		to a joinable thread");
	else if (status == ESRCH)
		printf(RED "No thread could be found");
	else if (status == EDEADLK)
		printf(RED "A deadlock was detected");
}

bool	thread_handler(pthread_t *th, void *(*foo)(void *), void *data,
t_opcode opcode)
{
	if (opcode == CREATE && pthread_create(th, NULL, foo, data) != 0)
	{
		print_thread_error(pthread_create(th, NULL, foo, data), opcode);
		return (false);
	}
	else if (opcode == JOIN && pthread_join(*th, NULL) != 0)
	{
		print_thread_error(pthread_join(*th, NULL), opcode);
		return (false);
	}
	else if (opcode == DETACH && pthread_detach(*th) != 0)
	{
		print_thread_error(pthread_detach(*th), opcode);
		return (false);
	}
	return (true);
}

long	ft_gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf(RED "Failed to get time" RESET "\n");
		return (0);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	write_status(t_philo *philo, t_philo_status status)
{
	t_data	*data;
	long	elapsed_time;

	data = philo->data;
	mutex_handler(&data->write_mutex, LOCK);
	elapsed_time = ft_gettime() - data->start_simulation;
	if (status == DIED)
		printf(GREEN "%-6ld" RED "%d died" RESET "\n",
			elapsed_time, philo->id);
	if (end_simulation(data, philo))
		return (mutex_handler(&data->write_mutex, UNLOCK));
	else if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		printf(GREEN "%-6ld" CYAN "%d has taken a fork"
			RESET "\n", elapsed_time, philo->id);
	else if (status == EAT)
		printf(GREEN "%-6ld" CYAN "%d is eating" RESET "\n",
			elapsed_time, philo->id);
	else if (status == SLEEP)
		printf(GREEN "%-6ld" CYAN "%d is sleeping" RESET "\n",
			elapsed_time, philo->id);
	else if (status == THINK)
		printf(GREEN "%-6ld" CYAN "%d is thinking" RESET "\n",
			elapsed_time, philo->id);
	mutex_handler(&data->write_mutex, UNLOCK);
	return (0);
}

/* micro sec */
void	ft_usleep(long consumed_time)
{
	long	start;

	start = ft_gettime();
	while (ft_gettime() - start < consumed_time)
	{
		usleep(100);
	}
}
