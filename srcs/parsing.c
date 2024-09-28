/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:13:35 by jjaroens          #+#    #+#             */
/*   Updated: 2024/09/28 13:49:07 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// TODO: 1) change string to number
//		2) make sure that the number > INT_MAX
//		3) timestamps > 60 ms (why need to be more than 60 ms?)

// to rewrite the parsing functions

static bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
// check if only allow characters for an argument

static const char *check_valid(const char *str)
{
	// to rewrite this function
	int	i;
	int len;
	const char *num;
	
	i = 0;
	len = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		exit_error("Only positive value is allowed.");
	if (!is_digit(str[i]))
		exit_error("Only digits are allowed");
	num = &str[i];
	while (is_digit(str[i]))
	{
		i++;
		len++;
	}
	if (len > 10)
		exit_error("The value is too big.");
	return (num);
}

long	ft_atol(const char *str)
{
	int i;
	long res;

	if (!str)
		return (0);
	// check if the argument is valid?
	str = check_valid(str);
	res = 0;
	i = 0;
	while (str[i])
	{
		res = res * 10;
		res = res + (str[i] - '0');
		i++;
	}
	if (res > INT_MAX)
		exit_error("The value exceeds INT_MAX");
	return (res);
}

void	parse_input(char **argv, t_data *data)
{
	data->num_philo = (int)ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]); 
	// limit for each activity timestamp
	if (argv[5])
		data->limit_meals = (int)ft_atol(argv[5]);
	else
		data->limit_meals = -1;
}