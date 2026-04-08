/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:06:59 by equentin          #+#    #+#             */
/*   Updated: 2026/04/08 17:25:05 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
#include "coders/codexion.h"
#include "coders/dongles.h"
#include "coders/parsing.h"
#include "coders/utils.h"
#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int				i;
	t_parsed		parsed;
	t_data			data;

	if (parse(&parsed, ac, av))
		return (1);
	data.parsed = &parsed;
	if (pthread_mutex_init(&data.print, NULL) != 0)
		return (1);
	init_dongles(&data);
	init_coders(&data);
	data.start_time = get_time();
	i = 0;
	while (i < data.parsed->number_of_coders)
	{
		pthread_create(&data.coders[i].thread, NULL, coder_routine, &data.coders[i]);
		usleep(1);
		i++;
	}

	i = 0;
	while (i < data.parsed->number_of_coders)
		pthread_join(data.coders[i++].thread, NULL);
	destroy_dongles(&data, data.parsed->number_of_dongles);
	free(data.coders);
	pthread_mutex_destroy(&data.print);
	return (0);
}
