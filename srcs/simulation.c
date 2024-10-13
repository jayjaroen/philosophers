/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:23:36 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/13 22:50:41 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
//to start simulation
/* 1. create a thread, philo thread
    2. monitoring the thread process
    3. every philo start simulaneously
    4. Join thread
*/
static bool	are_all_full(t_data *data)
{
	int	i;
	t_philo	*philo;
	
	i = -1;
	philo = data->philos;
	// printf("----------Inside are_all_full function------------\n");
	// printf("no philo: %d \n", data->num_philo);
	// printf(RED "are all full add: %p" RESET "\n", data);
	while (++i < data->num_philo)
	{
		// printf(RED "philo no %d %d" RESET "\n", philo[i].id, philo[i].is_full);
		//lock full?
		if (!philo[i].is_full)
			return (false);
	}
	return (true);
}
static bool is_dead(t_data *data)
{
	int	i;
	long	current;
	t_philo	*philo;
	
	i = -1;
	philo = data->philos;
	// printf("---------Inside is_dead function----------------\n");
	// printf("the address of data in is_dead: %p\n", data);
	while (++i < data->num_philo)
	{
		current = ft_gettime();
		mutex_handler(&data->meal_mutex, LOCK);
		if (philo[i].last_meal_time == 0)//set the start time of simulation
			philo[i].last_meal_time = data->start_simulation;
		// printf(RED "current time: %ld" RESET "\n", current);
		// printf(YELLOW "Time to die: %ld" RESET "\n", data->time_to_die);
		// printf(CYAN"current - philo_last_meal_time = %ld" RESET "\n",current - philo[i].last_meal_time);
		// printf(CYAN "last meal time is: %ld" RESET "\n", philo[i].last_meal_time);
		if ((current - philo[i].last_meal_time) > data->time_to_die)
		{
			mutex_handler(&data->meal_mutex, UNLOCK);
			mutex_handler(&data->end_mutex, LOCK);
			data->end_simulation = true;
			mutex_handler(&data->end_mutex, UNLOCK);
			write_status(philo, DIED);
			return (true);
		}
		mutex_handler(&data->meal_mutex, UNLOCK);
	}
	return (false);
}

static void	*thread_monitor(void *args)
{
	t_data *data;

	data = (t_data *)args;
	// printf(YELLOW "I am in the thread monitoring loop" RESET "\n");
	if (data->num_philo == 1)
		return (NULL);
	while (true)
	{
		// printf(RED "I am here" RESET "\n");
		if (are_all_full(data))
		{
			mutex_handler(&data->end_mutex, LOCK);
			// printf(YELLOW "ALL full" RESET "\n");
			data->end_simulation = true;
			mutex_handler(&data->end_mutex, UNLOCK);
			return (NULL);
		}
		if (is_dead(data))
			return (NULL);
	}
	// printf(YELLOW "at the end of function thread monitor" RESET "\n");
	return (NULL);
}

static void	*philo_simulation(void *args)
{
	t_philo *philo;
	t_data	*data;
	
	philo = (t_philo*)args;
	data = philo->data;	
    if	(data->num_philo == 1)
	{
		one_philo(data, philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(100);
	while (true)
	{
		eating(philo);
		if (philo->is_full || data->end_simulation)
			break ;
		// if (end_simulation(data))
		// 	break ;
		sleeping(philo);
		thinking(philo);
		// printf(YELLOW "Hi I am at the end of the loop" RESET "\n");
	}
	return (NULL);
}

bool	start_simulation(t_data *data)
{
	int i;

	i = -1;
	data->start_simulation = ft_gettime();
	// printf(CYAN "the time is: %ld" RESET "\n", data->start_simulation);
	// printf("the num of philo: %d\n", data->num_philo);
	if (!thread_handler(&data->monitor, &thread_monitor, data, CREATE))
		return (false);
	while (++i < data->num_philo)
	{
		if (!thread_handler(&data->philos[i].thread_id, &philo_simulation, 
		&data->philos[i], CREATE))
			return (false);
	}
    i = -1;
    while (++i < data->num_philo)
	{
        if (!thread_handler(&data->philos[i].thread_id, NULL, NULL, JOIN))
			return (false);
	}
	if (!thread_handler(&data->monitor, NULL, NULL, JOIN))
		return (false);
	return (true);
}
