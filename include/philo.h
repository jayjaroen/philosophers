/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:59:35 by jjaroens          #+#    #+#             */
/*   Updated: 2024/09/21 16:41:50 by jjaroens         ###   ########.fr       */
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
/// BOLD color 1 instead of 0
// ARGS: ./philo [number_of_philo] [time_to_die] [time_to_eat] [time_to_sleep] [the_number_of_times_that_philo_must_eat(optional)]

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define RESET "\033[0m"
/// Data structure
// each philopher 
typedef struct s_data t_data;
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
	t_data		*table; // have accessing to all the data
}	t_philo;

typedef struct s_data
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
}	t_data;

//// fork is mulex in this context

// Initiation && parsing agruments
void	init_simulation(char **argv, t_data *data);

// Utility Function
int	ft_atoi(char *str);

#endif