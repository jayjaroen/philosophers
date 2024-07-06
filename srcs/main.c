/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:58:05 by jjaroens          #+#    #+#             */
/*   Updated: 2024/07/06 16:58:47 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// The program takes four arguments
// The fifth agrument is optional 
// ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
// can' use perror function
// Error prevention -> do later
// 1. checking the input agruments ( convert to number, check the validity of the input) ( positive sign is ok, not negative sign) 
// 2. Simulation of the table
// right fork = philo id - 1 &&bleft fork = (philo pos (philo id - 1) +1) % number of philos

void	*test(int num)
{
	printf(Magenta"Hello philo no. %i\n", num);
	sleep(2);
	return (NULL);
}

int main(int argc, char **argv)
{
	int i;
	int philo_num;
	t_philo philosophers[ft_atoi(argv[1])];
	
	i = 0;
	if (argc == 5 || argc == 6) // the fifth agrument is optional - how?
	{
		// TODO
		// 1. function to parse a data && error checking
		// 2. Initialize the data (e.g. number of philosophers, assigning forks)
		// 3. Routine // threads 
		// 4. monitor process --> philo dies
		// 5. threads finish && join
		// philo finish -> eat && die && join
		// while eat && sleep && finish eating + unlock fork 	
		while (i < 4)
		{
			philosophers[i].id = i + 1;
			if (pthread_create(&philosophers[i].thread_id, NULL, test(philosophers[i].id), NULL) != 0)
				exit(EXIT_FAILURE);
			i++;
		}
		i = 0;
		while (i < 4)
		{
			if (pthread_join(philosophers[i].thread_id, NULL) != 0)
				exit(EXIT_FAILURE);
			i++;
		}		
	}
	else
	{
		printf(Red"Check arguments\n");
		exit (EXIT_FAILURE);
	}
	
}