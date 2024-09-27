/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:13:54 by jjaroens          #+#    #+#             */
/*   Updated: 2024/09/25 15:41:40 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// eat function
// TODO: 1) grab the forks-> lock mutex
//  2) start to eat (write function, update meal counter after finished the 
// time update is_full -> only for one philo)
// 3) release fork ->unlock mutex
void    eating(t_philo *philo)
{
    // talking fork
    mutex_handler(&(philo->first_fork->fork), LOCK);
    printf(YELLOW "am i here? in eating" RESET "\n");
    write_status(philo, TAKE_FIRST_FORK);
    mutex_handler(&(philo->second_fork->fork), LOCK);
    write_status(philo, TAKE_SECOND_FORK);
    // set value of philo
    mutex_handler(&(philo->philo_mutex), LOCK);
    philo->last_meal_time = ft_gettime();
    philo->meal_counter++;
    write_status(philo, EAT);
    mutex_handler(&(philo->philo_mutex), UNLOCK);
    // should the following be inside the mutex_handler
    ft_usleep(philo->data->time_to_eat);
    /// if full, set full
    if (philo->data->limit_meals > 0 && philo->meal_counter
        == philo->data->limit_meals)
    {
        mutex_handler(&(philo->philo_mutex), LOCK);
        philo->is_full = true;
        mutex_handler(&(philo->philo_mutex), UNLOCK);
    }
    //unlock the fork
    mutex_handler(&(philo->first_fork->fork), UNLOCK);
    mutex_handler(&(philo->second_fork->fork), UNLOCK);  
}

void    thinking(t_philo *philo)
{
    write_status(philo, THINK);
}