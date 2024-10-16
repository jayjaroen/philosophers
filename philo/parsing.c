/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:13:35 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/18 22:24:17 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_digit(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char	*check_valid(const char *str)
{
	int			i;
	int			j;
	const char	*num;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
	{
		printf(RED "Only positive value is allowed." RESET "\n");
		return (NULL);
	}
	j = i;
	if (!is_digit(&str[i]))
	{
		printf(RED "Only digit is allowed." RESET "\n");
		return (NULL);
	}
	num = &str[j];
	return (num);
}

static long	ft_atol(const char *str)
{
	int		i;
	long	res;

	if (!str)
		return (0);
	str = check_valid(str);
	if (str == NULL)
		return (-1);
	res = 0;
	i = 0;
	while (str[i])
	{
		res = res * 10;
		res = res + (str[i] - '0');
		i++;
	}
	if (res > INT_MAX)
	{
		printf(RED "The value exceeds INI_MAX" RESET "\n");
		return (-1);
	}
	return (res);
}

bool	parse_input(char **argv, t_data *data)
{
	data->num_philo = (int)ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->limit_meals = (int)ft_atol(argv[5]);
	else
		data->limit_meals = -1;
	if (data->num_philo == -1 || data->time_to_die == -1
		|| data->time_to_eat == -1 || data->time_to_sleep == -1)
		return (false);
	if (data->limit_meals == 0)
	{
		printf(RED "limit meal == 0. No simulation" RESET "\n");
		return (false);
	}
	return (true);
}
