/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:08:42 by jjaroens          #+#    #+#             */
/*   Updated: 2024/07/06 15:10:49 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(char *str)
{
	int i;
	int res;

	i = 0;
	res = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		res = res * 10;
		res = res + (str[i] - '0');
		i++;
	}
	return (res);
}