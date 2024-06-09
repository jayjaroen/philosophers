/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:59:35 by jjaroens          #+#    #+#             */
/*   Updated: 2024/06/09 15:45:15 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h> // gettimeofday
# include <limits.h>

/// Data structure
// each philopher 
typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_table
{
	int		num_philo;
	long	time_to_die; //shouldn't this be in the philo struct?
	long	time_to_eat;
	long	time_to_sleep;
	long	limit_meals; //optional the fifth agrument
	long	start_simulation; //timestamp
	bool	end_simulation; //on philo is dead || all philo is full (what would be a condition for this? --> limit number of meals)
	t_fork	*forks; //array to all the forks
	t_philo	*philos; //array to all the philos
}	t_table;

typedef struct s_philo
{
	int			id;
	long		meal_counter;
	long		last_meal_time;
	bool		is_full;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id; //each philo is a thread	
	t_table		*table; // but only one table
}	t_philo;
//// fork is mulex in this context

#endif