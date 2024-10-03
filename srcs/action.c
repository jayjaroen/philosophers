/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:13:54 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/03 16:33:51 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// eat function
// TODO: 1) grab the forks-> lock mutex
//  2) start to eat (write function, update meal counter after finished the 
// time update is_full -> only for one philo)
// 3) release fork ->unlock mutex
void	eating(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	mutex_handler(philo->first_fork, LOCK);
	write_status(philo, TAKE_FIRST_FORK);
	mutex_handler(philo->second_fork, LOCK);
	write_status(philo, TAKE_SECOND_FORK);
	mutex_handler(&data->philo_mutex, LOCK);
	philo->last_meal_time = ft_gettime();
	write_status(philo, EAT);
	ft_usleep(philo->data->time_to_eat);
	philo->meal_counter++;
	printf(MAGENTA"Philo %d : meal counter: %ld" RESET "\n",philo->id, philo->meal_counter);
	mutex_handler(&data->philo_mutex, UNLOCK);
	if (philo->meal_counter == data->limit_meals)
	{
		mutex_handler(&data->philo_mutex, LOCK);
		philo->is_full = true;
		mutex_handler(&data->philo_mutex, UNLOCK);
	}
	mutex_handler(philo->first_fork, UNLOCK);
	write_status(philo, LET_GO_FIRST); // to delete debug
	mutex_handler(philo->second_fork, UNLOCK);
	write_status(philo, LET_GO_SECOND);
	// die monitor the process
}

void    thinking(t_philo *philo)
{
	write_status(philo, THINK);
}

void	sleeping(t_philo *philo)
{
	write_status(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep);	
}