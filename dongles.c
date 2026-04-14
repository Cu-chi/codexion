/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:22:18 by equentin          #+#    #+#             */
/*   Updated: 2026/04/14 16:11:44 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
#include "coders/codexion.h"
#include "coders/dongles.h"
#include "coders/queue.h"
#include "coders/utils.h"

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

void	request_dongles(t_coder *coder)
{
	t_data			*data;
	struct timespec	target;
	int				wait_time;

	data = coder->data;
	pthread_mutex_lock(&data->table_mutex);
	enqueue(data, coder);
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
			target = get_target_timespec(wait_time);
			pthread_cond_timedwait(&data->table_cond, &data->table_mutex,
				&target);
		}
		else
			break ;
	}
	if (check_exit(data))
	{
		pthread_mutex_unlock(&data->table_mutex);
		return ;
	}
	dequeue(data, coder);
	coder->dongle_left->in_use = 1;
	coder->dongle_right->in_use = 1;
	pthread_mutex_unlock(&data->table_mutex);
	lock_ordered(coder);
}

void	release_dongles(t_coder *coder)
{
	t_data	*data;
	long	available_at;

	data = coder->data;
	pthread_mutex_lock(&data->table_mutex);
	coder->dongle_left->in_use = 0;
	coder->dongle_right->in_use = 0;
	available_at = get_time() + data->parsed->dongle_cooldown;
	coder->dongle_left->available_at = available_at;
	coder->dongle_right->available_at = available_at;
	pthread_mutex_unlock(&coder->dongle_left->mutex);
	pthread_mutex_unlock(&coder->dongle_right->mutex);
	pthread_cond_broadcast(&data->table_cond);
	pthread_mutex_unlock(&data->table_mutex);
}

void	destroy_dongles(t_data *data, int destroy_lim)
{
	int	i;

	i = 0;
	while (i < destroy_lim)
		pthread_mutex_destroy(&data->dongles[i++].mutex);
	free(data->dongles);
}

void	*init_dongles(t_data *data)
{
	int	i;

	i = 0;
	data->dongles = malloc(sizeof(t_dongle) * data->parsed->number_of_dongles);
	if (data->dongles == NULL)
		return (NULL);
	while (i < (data->parsed->number_of_dongles))
	{
		if (pthread_mutex_init(&data->dongles[i].mutex, NULL) != 0)
		{
			destroy_dongles(data, i);
			return (NULL);
		}
		i++;
	}
	return (data->dongles);
}
