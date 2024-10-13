/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:58:05 by jjaroens          #+#    #+#             */
/*   Updated: 2024/10/13 22:41:05 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
	t_data	data;
	
	memset(&data, 0, sizeof(t_data));
	printf(RED "addr before %p" RESET "\n", &data);
	if (argc == 5 || argc == 6)
	{
		if (!parse_input(argv, &data))//revise
		{
			clean_data(&data);//memset to zero
			return (EXIT_FAILURE);
		}
		if (!data_init(&data))
		{
			clean_data(&data);
			return (EXIT_FAILURE);
		}
		if (!start_simulation(&data))
		{
			clean_data(&data);
			return (EXIT_FAILURE);
		}
		clean_data(&data);
	}
	else
	{
		printf(RED "Check the number of arguments" RESET "\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
