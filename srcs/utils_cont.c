/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cont.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:05:12 by jjaroens          #+#    #+#             */
/*   Updated: 2024/09/23 22:08:18 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
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
    else if (opcode == INIT)
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