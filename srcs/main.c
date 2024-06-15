/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:58:05 by jjaroens          #+#    #+#             */
/*   Updated: 2024/06/15 14:57:32 by jjaroens         ###   ########.fr       */
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

int main(int argc, char **argv)
{
	if (argc == 1 || argc < 6) // the fifth agrument is optional
	{
		printf(RED "Error: Check agrument\n");
		exit (EXIT_FAILURE);
	}
	// TODO
	// 1. function to parse a data && error checking
	// 2. Initialize the data (e.g. number of philosophers, assigning forks)
	// 3. Routine // threads 
	// 4. monitor process --> philo dies
	// 5. threads finish && join
	// philo finish -> eat && die && join
	// while eat && sleep && finish eating + unlock fork 
}