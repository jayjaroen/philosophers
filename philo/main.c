/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:58:05 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/18 22:24:10 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	start_program(char **argv, t_data *data)
{
	if (!parse_input(argv, data))
	{
		clean_data(data);
		return (false);
	}
	if (!data_init(data))
	{
		clean_data(data);
		return (false);
	}
	if (!start_simulation(data))
	{
		clean_data(data);
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc == 5 || argc == 6)
	{
		if (!start_program(argv, &data))
			return (EXIT_FAILURE);
		clean_data(&data);
	}
	else
	{
		printf(RED "Check the number of arguments" RESET "\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
