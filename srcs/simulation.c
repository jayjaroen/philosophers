/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:23:36 by jjaroens          #+#    #+#             */
/*   Updated: 2024/09/25 17:08:41 by jjaroens         ###   ########.fr       */
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

static void	philo_thread_status(pthread_mutex_t *mutex, t_philo *philo)
{
	// can move mutex here?
	mutex_handler(mutex, INIT);
    mutex_handler(mutex, LOCK);
    printf(GREEN "thread id no: %d starting" RESET "\n", philo->id);
    philo->thread_status = true;
    printf(GREEN "the status of: %s" RESET "\n", philo->thread_status ? "true" : "false");
    mutex_handler(mutex, UNLOCK);
	printf("am i here?\n");
} 
static void	*philo_simulation(void *args)
{
// wait for every philo to start -> set value that threads are successfully created
// 
    t_philo *philo;
    pthread_mutex_t mutex;
    
	philo = (t_philo*)args;
	philo_thread_status(&mutex, philo);
    printf(CYAN "am I back here" RESET "\n");
	// while (!philo->data->end_simulation)
	// {
	// 	//EAT ( full?)
	// 	if (philo->is_full) //each philo
	// 		break ; //return what?
	// 	eating(philo);
	// 	thinking(philo);
		
	// 	//sleep
    // to sleep
	// 	//think (while waiting for fork can put into thinking?)
	// }
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
    }
    if (data->num_philo == 1)
        //TODO
        return ;
    i = -1;
    while (++i < data->num_philo)
        thread_handler(&data->philos[i].thread_id, &philo_simulation, &data->philos[i], CREATE);
    data->start_simulation = ft_gettime();
    printf(CYAN "the time is: %ld" RESET "\n", data->start_simulation);
	// Joining thread
    i = -1;
    while (++i < data->num_philo)
        thread_handler(&data->philos[i].thread_id, NULL, NULL, JOIN);
    // philo full && exit the program
}