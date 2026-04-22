/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 12:48:27 by equentin          #+#    #+#             */
/*   Updated: 2026/04/22 14:40:32 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/parsing.h"
#include "coders/codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	validate(t_parsed *parsed)
{
	if (parsed->number_of_coders <= 0 || parsed->time_to_burnout <= 0
		|| parsed->time_to_compile < 0 || parsed->time_to_debug < 0
		|| parsed->time_to_refactor < 0
		|| parsed->number_of_compiles_required < 0
		|| parsed->dongle_cooldown < 0)
	{
		fprintf(stderr, "Invalid value(s), all values except scheduler must be "
			"positive integer without sign, number_of_coders and "
			"time_to_burnout must be greater than 0\n");
		return (1);
	}
	if (strcmp(parsed->scheduler, "fifo") != 0 && strcmp(parsed->scheduler,
			"edf") != 0)
	{
		fprintf(stderr, "Invalid value, scheduler must be 'fifo' or 'edf'\n");
		return (1);
	}
	return (0);
}

int	check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (atoi(str));
}

int	parse(t_data *data, int ac, char **av)
{
	if (ac != 9)
	{
		fprintf(stderr,
			"Invalid format, expected:\n%s number_of_coders "
			"time_to_burnout time_to_compile time_to_debug "
			"time_to_refactor number_of_compiles_required "
			"dongle_cooldown scheduler\n",
			av[0]);
		return (1);
	}
	data->parsed.number_of_coders = check_num(av[1]);
	data->parsed.time_to_burnout = check_num(av[2]);
	data->parsed.time_to_compile = check_num(av[3]);
	data->parsed.time_to_debug = check_num(av[4]);
	data->parsed.time_to_refactor = check_num(av[5]);
	data->parsed.number_of_compiles_required = check_num(av[6]);
	data->parsed.dongle_cooldown = check_num(av[7]);
	data->parsed.scheduler = av[8];
	return (validate(&data->parsed));
}
