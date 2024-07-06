/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:59:35 by jjaroens          #+#    #+#             */
/*   Updated: 2024/07/06 16:52:12 by jjaroens         ###   ########.fr       */
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

/**ANSI escape codes are special sequences of characters that start with the 
	escape character (\033 or \x1b) followed by [ and end with a command.
	Has both foreground text color and blackground text*/
# define RED_BOLD "\033[1;31m" /*Bold red*/	
# define Red "\033[0;31m"
# define Green "\033[0;32m"
# define Yellow "\033[0;33m"
# define Blue "\033[0;34m"
# define Magenta "\033[0;35m"
# define Cyan "\033[0;36m"
# define White "\033[0;37m"
/// Data structure
// each philopher 
typedef struct s_table t_table;
typedef struct s_fork // fork is a mutex
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

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

//// fork is mulex in this context

int	ft_atoi(char *str);

#endif