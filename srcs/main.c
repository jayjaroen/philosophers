/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:58:05 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/12 16:15:25 by jjaroens         ###   ########.fr       */
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
	printf(RED "addr before %p" RESET "\n", &data);
	if (argc == 5 || argc == 6)
	{
		if (!parse_input(argv, &data))//revise
		{
			clean_data(&data);//memset to zero
			return (EXIT_FAILURE);
		}
		if (!data_init(&data))
		{
			clean_data(&data);
			return (EXIT_FAILURE);
		}
		start_simulation(&data);
		clean_data(&data);
		// 4) clean data: the case would be all the philos full or one is died
		// init_simulation(argv, &data);
		// passing the number of philo && other argument into the function
	}
	else
	{
		printf(RED "Check the number of arguments" RESET "\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
