/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:23:36 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/03 16:49:03 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
//to start simulation
/* 1. create a thread, philo thread
    2. monitoring the thread process
    3. every philo start simulaneously
    4. Join thread
*/
// static bool	simulation_finished(t_data *data)
// {
	
// }
static bool	are_all_full(t_data *data)
{
	int	i;
	t_philo *philo;
	
	i = -1;
	philo = data->philos;
	while (++i < data->num_philo)
	{
		if (!philo[i].is_full)
			return (false);
		i++;
	}
	return (true);
}
static void	*thread_monitor(void *args)
{
	t_data *data;
	t_philo *philo;
	long	current;
	int	i;

	data = (t_data *)args;
	philo = data->philos;
	i = -1;
	while (++i < data->num_philo)// should be while (true) -->check constantly
	{
		current = ft_gettime();
		if ((current - philo[i].last_meal_time) > data->time_to_die)//check if philo died
		{
			mutex_handler(&data->monitor_mutex, LOCK);
			printf(RED "the time is: %ld" RESET "\n", current - philo[i].last_meal_time);
			printf(RED "philo no: %d died" RESET "\n", philo[i].id);
			data->end_simulation = true;
			mutex_handler(&data->monitor_mutex, UNLOCK);
			break ;
		}
		if (are_all_full)
		{
			mutex_handler(&data->monitor_mutex, LOCK);
			printf(YELLOW "ALL full" RESET "\n");
			data->end_simulation = true;
			mutex_handler(&data->monitor_mutex, UNLOCK);
			break ;
		}
	}
	return (NULL);
}

static void	*philo_simulation(void *args)
{
	t_philo *philo;
	t_data	*data;
	
	philo = (t_philo*)args;
	data = philo->data;
    // printf(CYAN "am I back here" RESET "\n");
	// while (!philo->data->end_simulation)
	while (!data->end_simulation)
	{
		//EAT ( full?)
		if (philo->is_full)
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo);
		
		//sleep
    //to sleep
		//think (while waiting for fork can put into thinking?)
		// to check if all philo full == end simulation
	}
    return (NULL);
}

void	start_simulation(t_data *data)
{
	int i;

    if	(data->num_philo == 1)
		//TODO // enter the loop & died or handcoded?
		// no second fork // died
		// to write one philo function
		return ;
	i = -1;
	data->start_simulation = ft_gettime();
	printf(CYAN "the time is: %ld" RESET "\n", data->start_simulation);
	printf("the num of philo: %d\n", data->num_philo);
	thread_handler(&data->monitor, &thread_monitor, &data, CREATE);
	while (++i < data->num_philo)
	{
		thread_handler(&data->philos[i].thread_id, &philo_simulation, &data->philos[i], CREATE);
	}
	// Joining thread // starting to join at thread 0 first
    i = -1;
    while (++i < data->num_philo)
	{
        thread_handler(&data->philos[i].thread_id, NULL, NULL, JOIN);
	}
	free(data->philos);
}
