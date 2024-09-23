/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:59:35 by jjaroens          #+#    #+#             */
/*   Updated: 2024/09/23 22:25:33 by jjaroens         ###   ########.fr       */
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

typedef struct s_fork // fork is a mutex
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		meal_counter; // if all reach limit meal then end the simulation
	long		last_meal_time;
	bool		is_full;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id; //each philo is a thread	
	// pthread_mutex_t	philo_mutex; 
	bool		thread_status; //philo thread create?
	t_data		*data; // have accessing to all the data
}	t_philo;

typedef struct s_data
{
	int		num_philo;
	long	time_to_die; //shouldn't this be in the philo struct? 
	long	time_to_eat;
	long	time_to_sleep;
	int		limit_meals; //optional the fifth agrument
	bool	threads_ready;
	long	start_simulation; //timestamp
	bool	end_simulation; //on philo is dead || all philo is full (what would be a condition for this? --> limit number of meals)
	t_fork	*forks; //array to all the forks
	t_philo	*philos; //array to all the philos, double pointers?
}	t_data;

//// fork is mulex in this context

// Initiation && parsing agruments
void	parse_input(char **argv, t_data *data);
void	init_simulation(t_data *data);

// Utility Function
int	ft_atol(char const *str);
void	exit_error(const char *str);
void	*malloc_handler(size_t bytes);
void	mutex_error_handler(int status, t_opcode opcode);
void	mutex_handler(pthread_mutex_t *mutex, t_opcode opcode);
void	thread_error_handler(int status, t_opcode opcode);
void    thread_handler(pthread_t *th, void * (*foo)(void *), void *data, 
    t_opcode opcode);
long	ft_gettime(void);

// init
void    data_init(t_data *data);


#endif