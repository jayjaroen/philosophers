/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:06:01 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/12 15:22:16 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	destroy_mutex(t_data *data)
{
	int	i;
	
	i = -1;
	while (++i < data->num_philo)
	{
		mutex_handler(&data->forks[i], DESTROY);
	}
	mutex_handler(&data->write_mutex, DESTROY);// TO FIX this still link to exit error 
	mutex_handler(&data->philo_mutex, DESTROY);
	mutex_handler(&data->monitor_mutex, DESTROY);
	mutex_handler(&data->meal_mutex, DESTROY);
	mutex_handler(&data->end_mutex, DESTROY);	
}
void	clean_data(t_data *data)
{
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	if (data->forks)
	{
		destroy_mutex(data);
		free(data->forks);
		data->forks = NULL;
	}
	// free(data);//didn't malloc this
	memset(data, 0, sizeof(t_data));
}