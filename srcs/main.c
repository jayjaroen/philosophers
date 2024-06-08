/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaroens <jjaroens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:58:05 by jjaroens          #+#    #+#             */
/*   Updated: 2024/06/08 17:05:10 by jjaroens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// The program takes four arguments

int main(int argc, char **argv)
{
	if (argc == 1 || argc < 5)
	{
		perror("Error: Check agrument\n");
		exit (EXIT_FAILURE);
	}
}