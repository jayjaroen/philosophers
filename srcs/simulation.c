/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:23:36 by jjaroens          #+#    #+#             */
/*   Updated: 2024/09/23 22:30:18 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//to start simulation
/* 1. create a thread, philo thread
    2. monitoring the thread process
    3. every philo start simulaneously
    4. Join thread
*/
void    *simulation(void *args)
{
// wait for every philo to start
    t_philo *philo;
    pthread_mutex_t mutex;
    
    mutex_handler(&mutex, INIT);
    philo = (t_philo*)args;
    mutex_handler(&mutex, LOCK);
    philo->thread_status = true;
    mutex_handler(&mutex, UNLOCK);
    return (NULL);
}

void    init_simulation(t_data *data)
{
    int i;

    i = -1;
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
    while (++i < data->num_philo)
        thread_handler(&data->philos[i].thread_id, &simulation, &data->philos[i], CREATE);
    data->start_simulation = ft_gettime();
    
}