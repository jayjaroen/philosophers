/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:08:42 by jjaroens          #+#    #+#             */
/*   Updated: 2024/09/21 16:55:56 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// check for valid input: 1) check for negative, 2) change if the number is legit
// change for INT_MAX
// check len 
void	exit_error(const char *str)
{
	printf(RED"%s" RESET "\n", str);
	exit(EXIT_FAILURE);
}

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
	num = str[i];
	while (is_digit(str[i]))
	{
		i++;
		len++;
	}
	if (len > 10)
		exit_error("The value is too big.");
	return (num);
}

int	ft_atol(const char *str)
{
	int i;
	int res;
	char tmp;

	if (!str)
		return (0);
	// check if the argument is valid?
	str = check_input(str);
	res = 0;
	i = 0;
	while (str[i])
	{
		res = res * 10;
		res = res + (str[i] - '0');
		i++;
	}
	return (res);
}