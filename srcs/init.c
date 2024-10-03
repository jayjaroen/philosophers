/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:58:30 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/03 16:16:42 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	fork_mutex_init(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philo)
	{
		mutex_handler(&data->forks[i], INIT);
		i++;
	}
}

static void assigning_forks(t_philo *philo, t_data *data)
{
	int	pos;

	pos = philo->id - 1;
	if (data->num_philo == 1)
	{
		philo->first_fork = &data->forks[pos];
		return ;
	}
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &data->forks[(pos + 1) % data->num_philo];
		philo->second_fork = &data->forks[pos];
	}
	else
	{
		philo->first_fork = &data->forks[pos];
		philo->second_fork = &data->forks[(pos + 1) % data->num_philo];
	}
}

static void	philo_init(t_data *data)
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
		philo[i].data = data;
		philo[i].first_fork = NULL;
		philo[i].second_fork = NULL;
		assigning_forks(&philo[i], data);
		printf("philo no: %d first fork addr: %p\n", philo[i].id, philo[i].first_fork);
		printf("philo no: %d second fork addr: %p\n", philo[i].id, philo[i].second_fork);
	}
}

void    data_init(t_data *data)
{
    data->start_simulation = 0;
	data->end_simulation = false;
    // data->threads_ready = false;
    data->philos = (t_philo *) malloc_handler(sizeof(t_philo) * data->num_philo);
    data->forks = malloc_handler(sizeof(pthread_mutex_t) * data->num_philo);
    fork_mutex_init(data);
    philo_init(data);
	mutex_handler(&data->write_mutex, INIT);
	mutex_handler(&data->philo_mutex, INIT);
	mutex_handler(&data->monitor_mutex, INIT);
	mutex_handler(&data->end_mutex, INIT);
}
