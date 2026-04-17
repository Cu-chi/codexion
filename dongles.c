/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:22:18 by equentin          #+#    #+#             */
/*   Updated: 2026/04/17 18:58:32 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
#include "coders/codexion.h"
#include "coders/dongles.h"
#include "coders/queue.h"
#include "coders/utils.h"
#include <string.h>

int	check_dongles_availability(t_coder *coder)
{
	long	cur_time;
	long	left_delay;
	long	right_delay;

	left_delay = 0;
	right_delay = 0;
	cur_time = get_time();
	if (coder->dongle_left->in_use || coder->dongle_right->in_use)
		return (0);
	if (coder->dongle_left->available_at > cur_time)
		left_delay = coder->dongle_left->available_at - cur_time;
	if (coder->dongle_right->available_at > cur_time)
		right_delay = coder->dongle_right->available_at - cur_time;
	if (left_delay > 0 || right_delay > 0)
	{
		if (left_delay > right_delay)
			return (left_delay);
		return (right_delay);
	}
	return (-1);
}

void	wait_priority(t_coder *coder, t_data *data)
{
	int	wait_time;

	while (!check_exit(data))
	{
		if (is_priority_holder(data, coder) == 0)
		{
			pthread_cond_wait(&data->table_cond, &data->table_mutex);
			continue ;
		}
		wait_time = check_dongles_availability(coder);
		if (wait_time == 0)
			pthread_cond_wait(&data->table_cond, &data->table_mutex);
		else if (wait_time > 0)
		{
			pthread_mutex_unlock(&data->table_mutex);
			codexion_sleep(wait_time, data);
			pthread_mutex_lock(&data->table_mutex);
		}
		else
			break ;
	}
}

int	request_dongles(t_coder *coder)
{
	t_data	*data;

	data = coder->data;
	pthread_mutex_lock(&data->table_mutex);
	enqueue(data, coder); // TODO: protect malloc fail
	wait_priority(coder, data);
	if (check_exit(data))
	{
		pthread_mutex_unlock(&data->table_mutex);
		return (0);
	}
	dequeue(data, coder);
	coder->dongle_left->in_use = 1;
	coder->dongle_right->in_use = 1;
	pthread_mutex_unlock(&data->table_mutex);
	return (1);
}

void	release_dongles(t_coder *coder)
{
	t_data	*data;
	long	available_at;

	data = coder->data;
	pthread_mutex_lock(&data->table_mutex);
	coder->dongle_left->in_use = 0;
	coder->dongle_right->in_use = 0;
	available_at = get_time() + data->parsed.dongle_cooldown;
	coder->dongle_left->available_at = available_at;
	coder->dongle_right->available_at = available_at;
	pthread_cond_broadcast(&data->table_cond);
	pthread_mutex_unlock(&data->table_mutex);
}

int	init_dongles(t_data *data)
{
	int	i;

	i = 0;
	data->dongles = malloc(sizeof(t_dongle) * data->parsed.number_of_coders);
	if (data->dongles == NULL)
		return (1);
	memset(data->dongles, 0, sizeof(t_dongle) * data->parsed.number_of_coders);
	return (0);
}
