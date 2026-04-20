/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:06:59 by equentin          #+#    #+#             */
/*   Updated: 2026/04/20 11:09:35 by equentin         ###   ########.fr       */
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
	while (!check_finished(data) && !check_exit(data))
	{
		i = 0;
		while (i++ < data->parsed.number_of_coders)
		{
			if (has_burned_out(&data->coders[i - 1], &data->parsed))
			{
				pthread_mutex_lock(&data->exit_mutex);
				data->exit = 1;
				pthread_mutex_unlock(&data->exit_mutex);
				pthread_mutex_lock(&data->table_mutex);
				pthread_cond_broadcast(&data->table_cond);
				pthread_mutex_unlock(&data->table_mutex);
				print_lock(data, "%ld %d burned out\n", i, 1);
				return (NULL);
			}
		}
		usleep(100);
	}
	return (NULL);
}

int	create_coders(t_data *data, pthread_t *monitor_thread)
{
	int	i;
	int	init_res;

	i = 0;
	while (i < data->parsed.number_of_coders)
	{
		init_res = pthread_create(&data->coders[i].thread, NULL, coder_routine,
				&data->coders[i]);
		if (init_res)
			return (1);
		i += 2;
	}
	i = 1;
	usleep(10);
	while (i < data->parsed.number_of_coders)
	{
		init_res = pthread_create(&data->coders[i].thread, NULL, coder_routine,
				&data->coders[i]);
		if (init_res)
			return (1);
		i += 2;
	}
	pthread_create(monitor_thread, NULL, monitor, data);
	return (0);
}

void	destroy_all(t_data *data)
{
	free(data->dongles);
	free_queue(data->queue);
	destroy_coders(data, data->parsed.number_of_coders);
	destroy_mutex_cond(data, 4, 1);
}

int	init_all(t_data *data)
{
	if (init_mutexes_cond(data))
		return (1);
	if (init_dongles(data))
	{
		destroy_mutex_cond(data, 4, 1);
		return (1);
	}
	if (init_coders(data))
	{
		free(data->dongles);
		destroy_mutex_cond(data, 4, 1);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int			i;
	t_data		data;
	pthread_t	monitor_thread;

	memset(&data, 0, sizeof(t_data));
	if (parse(&data, ac, av))
		return (1);
	if (init_all(&data))
	{
		fprintf(stderr, "an error occured at program initialization\n");
		return (1);
	}
	data.start_time = get_time();
	if (create_coders(&data, &monitor_thread))
	{
		fprintf(stderr, "an error occured at coders initialization\n");
		destroy_all(&data);
		return (1);
	}
	i = 0;
	while (i < data.parsed.number_of_coders)
		pthread_join(data.coders[i++].thread, NULL);
	pthread_join(monitor_thread, NULL);
	destroy_all(&data);
	return (0);
}
