/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:13:35 by jjaroens          #+#    #+#             */
/*   Updated: 2024/09/21 16:42:07 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// TODO: 1) change string to number
//		2) make sure that the number > INT_MAX
//		3) timestamps > 60 ms


void	parse_input(char **argv, t_data *data)
{
	data->num_philo = ft_atol(argv[1]);
}