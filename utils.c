/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:18:25 by equentin          #+#    #+#             */
/*   Updated: 2026/04/17 18:02:26 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/codexion.h"
#include "coders/utils.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000 + tv.tv_usec) / 1000);
}

long	get_time_diff(long time)
{
	return (get_time() - time);
}

void	print_lock(t_data *data, char *fmt, int coder_id, int force)
{
	pthread_mutex_lock(&data->print_mutex);
	if (!check_exit(data) || force)
		printf(fmt, get_time_diff(data->start_time), coder_id);
	pthread_mutex_unlock(&data->print_mutex);
}

void	codexion_sleep(int ms, t_data *data)
{
	long	expires_at;

	expires_at = get_time() + ms;
	while (get_time() < expires_at && !check_exit(data))
		usleep(100);
}

int	have_same_dongle(t_coder *coder1, t_coder *coder2)
{
	if (coder1->dongle_left == coder2->dongle_right)
		return (1);
	if (coder1->dongle_right == coder2->dongle_left)
		return (1);
	if (coder1->dongle_left == coder2->dongle_left)
		return (1);
	if (coder1->dongle_right == coder2->dongle_right)
		return (1);
	return (0);
}
