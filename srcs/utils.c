/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:08:42 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/11 11:03:50 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// check for valid input: 1) check for negative, 2) change if the number is legit
// change for INT_MAX
// check len 
void	exit_error(const char *str)
{
	printf(RED"%s" RESET "\n", str);
	// calling free function
	// free fork, free philo
	exit(EXIT_FAILURE); // can't use exit
	// Free philo && fork if exit, import data//
}

void	*malloc_handler(size_t bytes)
{
	void	*res;
	
	res = malloc(bytes);
	if (!res)
		exit_error("Failed to malloc");
	return (res);
}

void	mutex_error_handler(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		exit_error("The value specified by mutex is invalid.");
	else if (status == EINVAL && opcode == INIT)
		exit_error("The value specified by attr is invalid.");
	else if (status == EINVAL && opcode == DESTROY)
		exit_error("The value specified by mutex is invalid.");
	else if (status == EBUSY)
		exit_error("Mutex is locked.");
	else if (status == ENOMEM)
		exit_error("The process cannot allocate enough memory to create another mutex.");
	else if (status == EPERM)
		exit_error("The current thread does not hold a lock on mutex.");
	else if (status == EDEADLK)
		exit_error("The current thread does not hold a lock on mutex.");	
}
// mutex handling /// LOCK, UNLOCK, INIT, DESTROY
void	mutex_handler(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		mutex_error_handler(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		mutex_error_handler(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		mutex_error_handler(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		mutex_error_handler(pthread_mutex_destroy(mutex), opcode);
	else
		exit_error("Wrong operation code for mutex");
}
