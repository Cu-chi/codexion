/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:18:25 by equentin          #+#    #+#             */
/*   Updated: 2026/04/15 16:40:40 by equentin         ###   ########.fr       */
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
	int		ms_waited;
	long	expires_at;

	ms_waited = 0;
	expires_at = get_time() + ms;
	while (get_time() < expires_at && !check_exit(data))
		usleep(0);
}
