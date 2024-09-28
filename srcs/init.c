/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:58:30 by jjaroens          #+#    #+#             */
/*   Updated: 2024/09/28 16:18:19 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void    fork_init(t_data *data)
{
    int i;
    
    i = -1;
    while (++i < data->num_philo)
    {
        mutex_handler(&data->forks[i].fork, INIT);
        data->forks[i].fork_id = i; // fork start at 0;
    }
}

static void assigning_forks(t_philo *philo, t_fork *fork, int philo_pos)
{
    // Potential Deadlock assigning the value?
    // contested area?
    if (philo->id % 2 == 0) // even philo
    {
        philo->first_fork = &fork[philo_pos];
        philo->second_fork = &fork[(philo_pos + 1) % philo->data->num_philo];      
    }
    else // odd philo
    {
        philo->first_fork = &fork[(philo_pos + 1) % philo->data->num_philo];
        philo->second_fork = &fork[philo_pos];
    }
    
}

static void    philo_init(t_data *data)
{
    int i;
    t_philo *philo;

    i = -1;
	philo = data->philos;
    while (++i < data->num_philo)
    {
        philo[i].id = i + 1;
        philo[i].is_full = false;
        philo[i].meal_counter = 0;
        philo[i].data = data; // point to the same set of data
        // mutex_handler(&philo->philo_mutex, INIT);
        assigning_forks(philo, data->forks, i);
    }    
}

void    data_init(t_data *data)
{
    data->end_simulation = false;
    data->threads_ready = false;
    data->philos = (t_philo *) malloc_handler(sizeof(t_philo) * data->num_philo);
    data->forks = (t_fork *) malloc_handler(sizeof(t_fork) * data->num_philo);
	mutex_handler(&data->write_mutex, INIT);
	mutex_handler(&data->philo_mutex, INIT);
    philo_init(data);
    fork_init(data);
    
}
