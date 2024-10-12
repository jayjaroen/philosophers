/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:59:35 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/12 15:51:17 by jjaroens         ###   ########.fr       */
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
# include <errno.h>
# include <string.h>

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

typedef enum e_philo_status
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	LET_GO_FIRST, //TO DELETE should I include this?
	LET_GO_SECOND,
	DIED,
}	t_philo_status;

typedef enum e_opcode
{
	CREATE,
	INIT,
	LOCK,
	UNLOCK,
	DETACH,
	JOIN,
	DESTROY,
} t_opcode;

typedef struct s_philo
{
	int			id;
	long		meal_counter; // if all reach limit meal then end the simulation
	long		last_meal_time;
	bool		is_full;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_t	thread_id; //each philo is a thread	
	t_data		*data; // have accessing to all the data
}	t_philo;

typedef struct s_data
{
	int	num_philo;
	long	time_to_die; //shouldn't this be in the philo struct? 
	long	time_to_eat;
	long	time_to_sleep;
	int	limit_meals; //optional the fifth agrument
	long	start_simulation; //timestamp
	bool	end_simulation; //on philo is dead || all philo is full (what would be a condition for this? --> limit number of meals)
	pthread_t	monitor;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t meal_mutex;
	pthread_mutex_t	monitor_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t *forks;
	t_philo	*philos;
}	t_data;

//// fork is mulex in this context

// Parsing agruments
bool	parse_input(char **argv, t_data *data);

// Simulation
void	write_status(t_philo *philo, t_philo_status status);
void	start_simulation(t_data *data);
void	eating(t_philo *philo);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	one_philo(t_data *data, t_philo *philo);

// Utility Function
void	exit_error(const char *str);
// void	*malloc_handler(size_t bytes);
void	mutex_error_handler(int status, t_opcode opcode);
void	mutex_handler(pthread_mutex_t *mutex, t_opcode opcode);
void	thread_error_handler(int status, t_opcode opcode);
void    thread_handler(pthread_t *th, void * (*foo)(void *), void *data, 
    t_opcode opcode);
long	ft_gettime(void);
void	ft_usleep(long consumed_time);

// init
bool	data_init(t_data *data);

//clean data
void	clean_data(t_data *data);

#endif