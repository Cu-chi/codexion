/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:06:59 by equentin          #+#    #+#             */
/*   Updated: 2026/04/15 11:00:58 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
#include "coders/codexion.h"
#include "coders/dongles.h"
#include "coders/mutexes.h"
#include "coders/parsing.h"
#include "coders/utils.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	*monitor(void *data_ptr)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_ptr;
	while (!check_exit(data) && !check_finished(data))
	{
		i = 0;
		while (i++ < data->parsed->number_of_coders)
		{
			if (has_burned_out(&data->coders[i - 1], data->parsed))
			{
				print_lock(data, "%ld %d burned out\n", i);
				pthread_mutex_lock(&data->exit_mutex);
				data->exit = 1;
				pthread_mutex_unlock(&data->exit_mutex);
				pthread_mutex_lock(&data->table_mutex);
				pthread_cond_broadcast(&data->table_cond);
				pthread_mutex_unlock(&data->table_mutex);
				return (NULL);
			}
		}
		usleep(1);
	}
	return (NULL);
}

int	create_coders(t_data *data, pthread_t *monitor_thread)
{
	int	i;

	i = 0;
	while (i < data->parsed->number_of_coders)
	{
		pthread_create(&data->coders[i].thread, NULL, coder_routine,
			&data->coders[i]);
		usleep(1);
		i += 2;
	}
	i = 1;
	while (i < data->parsed->number_of_coders)
	{
		pthread_create(&data->coders[i].thread, NULL, coder_routine,
			&data->coders[i]);
		usleep(1);
		i += 2;
	}
	pthread_create(monitor_thread, NULL, monitor, data);
	return (0);
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
	init_mutexes_cond(&data);
	init_dongles(&data);
	init_coders(&data);
	data.start_time = get_time();
	create_coders(&data, &monitor_thread);
	i = 0;
	while (i < data.parsed->number_of_coders)
		pthread_join(data.coders[i++].thread, NULL);
	pthread_join(monitor_thread, NULL);
	free(data.dongles);
	free_queue(data.queue);
	destroy_coders(&data, data.parsed->number_of_coders);
	destroy_mutex_cond(&data, 4, 1);
	return (0);
}
