/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:13:54 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/14 16:22:37 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	is_full(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->meal_counter == data->limit_meals && (data->limit_meals > 0))
	{
		mutex_handler(&data->philo_mutex, LOCK);
		philo->is_full = true;
		mutex_handler(&data->philo_mutex, UNLOCK);
	}
}

void	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	mutex_handler(philo->first_fork, LOCK);
	write_status(philo, TAKE_FIRST_FORK);
	mutex_handler(philo->second_fork, LOCK);
	write_status(philo, TAKE_SECOND_FORK);
	write_status(philo, EAT);
	ft_usleep(philo->data->time_to_eat);
	mutex_handler(&data->meal_mutex, LOCK);
	philo->last_meal_time = ft_gettime();
	philo->meal_counter++;
	mutex_handler(&data->meal_mutex, UNLOCK);
	is_full(philo);
	mutex_handler(philo->second_fork, UNLOCK);
	mutex_handler(philo->first_fork, UNLOCK);
}

void	thinking(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	write_status(philo, THINK);
	if (data->num_philo % 2 == 1 && data->time_to_eat >= data->time_to_sleep)
	{
		ft_usleep(data->time_to_eat * 2 - data->time_to_sleep);
	}
}

void	sleeping(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	write_status(philo, SLEEP);
	ft_usleep(data->time_to_sleep);
}

void	one_philo(t_data *data, t_philo *philo)
{
	write_status(philo, TAKE_FIRST_FORK);
	ft_usleep(data->time_to_die);
	write_status(philo, DIED);
}
