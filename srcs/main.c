/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:58:05 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/05 14:21:27 by jjaroens         ###   ########.fr       */
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
// number of philo /2 -> the number of philo can eat at the same time?
// Init the table

// TODO
// 1. function to parse a data && error checking
// 2. Initialize the data (e.g. number of philosophers, assigning forks)
// 3. Routine // threads 
// 4. monitor process --> philo dies
// 5. threads finish && join
// philo finish -> eat && die && join
// while eat && sleep && finish eating + unlock fork 	

int main(int argc, char **argv)
{
	t_data	data;
	
	memset(&data, 0, sizeof(t_data));
	// set zero data;
	printf(RED "addr before %p" RESET "\n", &data);
	if (argc == 5 || argc == 6)
	{
		// to init the simulation;
		// TODO: 1) Passing Argument; 
		parse_input(argv, &data);
		//2) Data Initiation // 
		data_init(&data);
		//3) start simulation
		start_simulation(&data);
		// 4) clean data: the case would be all the philos full or one is died
		// init_simulation(argv, &data);
		// passing the number of philo && other argument into the function
	}
	else
	{
		exit_error("Please check the number of arguments");
	}
	return (0);
}
// int main(int argc, char **argv)
// {
// 	int i;
// 	int philo_num;
// 	t_philo philo;
	
// 	philo_num = ft_atoi(argv[1]);
// 	philo = malloc(sizeof(t_philo) * philo_num);
// 	pthread_mutex_init(&test_philo, NULL);
	
// 	i = -1;
// 	if (argc == 2) // the fifth agrument is optional - how?
// 	{
// 		while (++i < philo_num + 1)
// 		{
// 			philo[i].id = i + 1;
// 			if (pthread_create(&philo[i].id, NULL, &test, (void *)philo[i].id) != 0)
// 			{
// 				printf(RED "Failed to create threat" RESET "\n");
// 				// to free malloc philo
// 				exit(EXIT_FAILURE);
// 			}
// 		}
// 		i = -1;
// 		while (++i <= ft_atoi(argv[1]))
// 		{
// 			if (pthread_join(philo[i].id, NULL) != 0)
// 				exit(EXIT_FAILURE);
// 		}		
// 	}
// 	else
// 	{
// 		printf(RED "Check arguments" RESET "\n");
// 		exit (EXIT_FAILURE);
// 	}
// 	// to free malloc philo
// 	return (0);
// 	pthread_mulex_destroy(&test_philo); //destroy mulex in each fork
// }