/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:23:36 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/18 22:24:23 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	are_all_full(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = data->philos;
	while (++i < data->num_philo)
	{
		if (!philo[i].is_full)
			return (false);
	}
	return (true);
}

static bool	is_dead(t_data *data)
{
	int		i;
	long	current;
	t_philo	*philo;

	i = -1;
	philo = data->philos;
	while (++i < data->num_philo)
	{
		mutex_handler(&data->meal_mutex, LOCK);
		current = ft_gettime();
		if ((current - philo[i].last_meal_time) > data->time_to_die)
		{
			mutex_handler(&data->meal_mutex, UNLOCK);
			mutex_handler(&data->end_mutex, LOCK);
			data->end_simulation = true;
			mutex_handler(&data->end_mutex, UNLOCK);
			write_status(&philo[i], DIED);
			return (true);
		}
		mutex_handler(&data->meal_mutex, UNLOCK);
	}
	return (false);
}

static void	*thread_monitor(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	if (data->num_philo == 1)
		return (NULL);
	while (true)
	{
		if (are_all_full(data))
		{
			mutex_handler(&data->end_mutex, LOCK);
			data->end_simulation = true;
			mutex_handler(&data->end_mutex, UNLOCK);
			return (NULL);
		}
		if (is_dead(data))
			return (NULL);
	}
	return (NULL);
}

static void	*philo_simulation(void *args)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)args;
	data = philo->data;
	if (data->num_philo == 1)
	{
		one_philo(data, philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(100);
	while (true)
	{
		if (end_simulation(data, philo))
			break ;
		eating(philo);
		if (end_simulation(data, philo))
			break ;
		sleeping(philo);
		if (end_simulation(data, philo))
			break ;
		thinking(philo);
	}
	return (NULL);
}

bool	start_simulation(t_data *data)
{
	int	i;

	i = -1;
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
