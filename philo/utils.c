/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:08:42 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/18 22:24:32 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	end_simulation(t_data *data, t_philo *philo)
{
	mutex_handler(&data->end_mutex, LOCK);
	if (data->end_simulation)
	{
		mutex_handler(&data->end_mutex, UNLOCK);
		return (true);
	}
	mutex_handler(&data->end_mutex, UNLOCK);
	mutex_handler(&data->philo_mutex, LOCK);
	if (philo->is_full)
	{
		mutex_handler(&data->philo_mutex, UNLOCK);
		return (true);
	}
	mutex_handler(&data->philo_mutex, UNLOCK);
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
