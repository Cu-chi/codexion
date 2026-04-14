/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:06:59 by equentin          #+#    #+#             */
/*   Updated: 2026/04/14 13:08:08 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
#include "coders/codexion.h"
#include "coders/dongles.h"
#include "coders/parsing.h"
#include "coders/utils.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	*monitor(void *data_ptr)
{
	t_data	*data;
	t_coder	*coder;
	int		i;

	data = (t_data *)data_ptr;
	while (!check_exit(data) && !check_finished(data))
	{
		i = 0;
		while (i++ < data->parsed->number_of_coders)
		{
			coder = &data->coders[i - 1];
			if (has_burned_out(coder, data->parsed))
			{
				print_lock(data, "%ld %d burned out\n", i);
				pthread_mutex_lock(&data->exit_mutex);
				data->exit = 1;
				pthread_mutex_unlock(&data->exit_mutex);
				pthread_mutex_lock(&data->table_mutex);
				pthread_cond_broadcast(&data->table_cond);
				pthread_mutex_unlock(&data->table_mutex);
			}
		}
		usleep(1);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	int			i;
	t_parsed	parsed;
	t_data		data;
	pthread_t	monitor_thread;

	memset(&data, 0, sizeof(t_data));
	if (parse(&parsed, ac, av))
		return (1);
	data.parsed = &parsed;
	if (pthread_mutex_init(&data.print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data.table_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data.print_mutex);
		return (1);
	}
	if (pthread_cond_init(&data.table_cond, NULL) != 0)
	{
		pthread_mutex_destroy(&data.print_mutex);
		pthread_mutex_destroy(&data.table_mutex);
		return (1);
	}
	if (pthread_mutex_init(&data.finished_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data.print_mutex);
		pthread_mutex_destroy(&data.table_mutex);
		pthread_cond_destroy(&data.table_cond);
		return (1);
	}
	if (pthread_mutex_init(&data.exit_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data.print_mutex);
		pthread_mutex_destroy(&data.finished_mutex);
		pthread_mutex_destroy(&data.table_mutex);
		pthread_cond_destroy(&data.table_cond);
		return (1);
	}
	init_dongles(&data);
	init_coders(&data);
	data.start_time = get_time();
	i = 0;
	while (i < data.parsed->number_of_coders)
	{
		pthread_create(&data.coders[i].thread, NULL, coder_routine,
			&data.coders[i]);
		usleep(1);
		i += 2;
	}
	i = 1;
	while (i < data.parsed->number_of_coders)
	{
		pthread_create(&data.coders[i].thread, NULL, coder_routine,
			&data.coders[i]);
		usleep(1);
		i += 2;
	}
	pthread_create(&monitor_thread, NULL, monitor, &data);
	i = 0;
	while (i < data.parsed->number_of_coders)
		pthread_join(data.coders[i++].thread, NULL);
	pthread_join(monitor_thread, NULL);
	destroy_dongles(&data, data.parsed->number_of_dongles);
	free(data.coders);
	pthread_mutex_destroy(&data.print_mutex);
	pthread_mutex_destroy(&data.table_mutex);
	pthread_mutex_destroy(&data.finished_mutex);
	pthread_mutex_destroy(&data.exit_mutex);
	pthread_cond_destroy(&data.table_cond);
	return (0);
}
