/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:58:30 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/14 16:04:59 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	fork_mutex_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf(RED "Failed to init fork mutex" RESET "\n");
			return (false);
		}
	}
	return (true);
}

static void	assigning_forks(t_philo *philo, t_data *data)
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
	int		i;
	t_philo	*philo;

	i = -1;
	philo = data->philos;
	while (++i < data->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].is_full = false;
		philo[i].meal_counter = 0;
		philo[i].last_meal_time = data->start_simulation;
		philo[i].data = data;
		philo[i].first_fork = NULL;
		philo[i].second_fork = NULL;
		assigning_forks(&philo[i], data);
	}
}

static bool	program_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->write_mutex, NULL)
		|| pthread_mutex_init(&data->philo_mutex, NULL)
		|| pthread_mutex_init(&data->meal_mutex, NULL)
		|| pthread_mutex_init(&data->monitor_mutex, NULL)
		|| pthread_mutex_init(&data->end_mutex, NULL))
	{
		printf(RED "Failed to init program mutex" RESET "\n");
		return (false);
	}
	return (true);
}

bool	data_init(t_data *data)
{
	data->start_simulation = ft_gettime();
	data->end_simulation = false;
	data->philos = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philos)
		return (false);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		return (false);
	if (!fork_mutex_init(data))
		return (false);
	philo_init(data);
	if (!program_mutex(data))
		return (false);
	return (true);
}
