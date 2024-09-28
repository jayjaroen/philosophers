/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:23:36 by jjaroens          #+#    #+#             */
/*   Updated: 2024/09/28 16:46:08 by jjaroens         ###   ########.fr       */
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
static void	*thread_monitor(void *args)
{
	t_data *data;
	t_philo *philo;
	long	current;
	int	i;

	data = (t_data *)args;
	philo = data->philos;
	i = 0;
	while (i < data->num_philo)
	{
		
		current = ft_gettime();
		if ((current - philo[i].last_meal_time) > data->time_to_die)
		{
			printf(RED "the time is: %ld" RESET "\n", current - philo[i].last_meal_time);
			printf(RED "philo no: %d died" RESET "\n", philo[i].id);
			break ;
		}
		i++;
	}
	return (NULL);
}

static void	philo_thread_status(pthread_mutex_t *mutex, t_philo *philo) // should I have this function?
{
	// can move mutex here?
	mutex_handler(mutex, INIT);
    mutex_handler(mutex, LOCK);
    // printf(GREEN "thread id no: %d starting" RESET "\n", philo->id);
    philo->thread_status = true;
    printf(GREEN "the status of: %s" RESET "\n", philo->thread_status ? "true" : "false");
    mutex_handler(mutex, UNLOCK);
	// printf("am i here?\n");
} 

static void	*philo_simulation(void *args)
{
// wait for every philo to start -> set value that threads are successfully created
// 
    t_philo *philo;
    pthread_mutex_t mutex;
    
	philo = (t_philo*)args;
	philo_thread_status(&mutex, philo);
    // printf(CYAN "am I back here" RESET "\n");
	// while (!philo->data->end_simulation)
	while (!philo->is_full)
	{
		//EAT ( full?)
		// if (philo->is_full) //all philo full // data// each philo simutanenously 
		// 	break ;
		printf("am I here?\n");
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

void    start_simulation(t_data *data)
{
    int i;

    /// check if philo is 1
    // create philo
    if (data->limit_meals == 0)
    {
        return ;
        // clear the data
		// exit
    }
    if (data->num_philo == 1)
        //TODO
		// no second fork // died 
        return ;
    i = -1;
    data->start_simulation = ft_gettime();
    printf(CYAN "the time is: %ld" RESET "\n", data->start_simulation);
	printf("the num of philo: %d\n", data->num_philo);
    while (++i < data->num_philo)
	{
        thread_handler(&data->philos[i].thread_id, &philo_simulation, &data->philos[i], CREATE);
	}
	thread_handler(&data->monitor, &thread_monitor, &data, CREATE);
	// Joining thread // starting to join at thread 0 first
    i = -1;
    while (++i < data->num_philo)
	{
        thread_handler(&data->philos[i].thread_id, NULL, NULL, JOIN);
	}
	free(data->philos);
}