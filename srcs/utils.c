/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:08:42 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/13 22:47:27 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// check for valid input: 1) check for negative, 2) change if the number is legit
// change for INT_MAX
// check len 
// void	exit_error(const char *str)
// {
// 	printf(RED"%s" RESET "\n", str);
// 	// calling free function
// 	// free fork, free philo
// 	exit(EXIT_FAILURE); // can't use exit
// 	// Free philo && fork if exit, import data//
// }

// void	*malloc_handler(size_t bytes)
// {
// 	void	*res;
	
// 	res = malloc(bytes);
// 	if (!res)
// 		exit_error("Failed to malloc");
// 	return (res);
// }
bool	end_simulation(t_data *data)
{
	mutex_handler(&data->end_mutex, LOCK);
	if (data->end_simulation)
	{
		mutex_handler(&data->end_mutex, UNLOCK);
		return (true);
	}
	return (false);
}

static void	print_mutex_error(int status, t_opcode opcode)
{
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		printf(RED "The value specified by mutex is invalid." RESET "\n");
	else if (status == EINVAL && opcode == INIT)
		printf(RED "The value specified by attr is invalid." RESET "\n");
	else if (status == EINVAL && opcode == DESTROY)
		printf(RED "The value specified by mutex is invalid." RESET "\n");
	else if (status == EBUSY)
		printf(RED "Mutex is locked." RESET "\n");
	else if (status == ENOMEM)
		printf(RED "The process cannot allocate enough memory to create \
		another mutex." RESET "\n");
	else if (status == EPERM)
		printf(RED "The current thread does not hold a lock on mutex." \
		RESET "\n");
	else if (status == EDEADLK)
		printf(RED "The current thread does not hold a lock on mutex." \
		RESET "\n");	
}
// mutex handling /// LOCK, UNLOCK, INIT, DESTROY
bool	mutex_handler(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == LOCK && pthread_mutex_lock(mutex) != 0)
	{
		print_mutex_error(pthread_mutex_lock(mutex), opcode);
		return (false);
	}
	else if (opcode == UNLOCK && pthread_mutex_unlock(mutex) != 0)
	{
		print_mutex_error(pthread_mutex_unlock(mutex), opcode);
		return (false);
	}
	else if (opcode == INIT && pthread_mutex_init(mutex, NULL) != 0)
	{
		print_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
		return (false);
	}
	else if (opcode == DESTROY && pthread_mutex_destroy(mutex) != 0)
	{
		print_mutex_error(pthread_mutex_destroy(mutex), opcode);
		return (false);
	}
	return (true);
}
