/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:18:25 by equentin          #+#    #+#             */
/*   Updated: 2026/04/13 13:20:36 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/codexion.h"
#include "coders/utils.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

ssize_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000 + tv.tv_usec) / 1000);
}

ssize_t	get_time_diff(ssize_t time)
{
	return (get_time() - time);
}

void	print_lock(t_data *data, char *fmt, int coder_id)
{
	pthread_mutex_lock(&data->print);
	if (!check_exit(data))
		printf(fmt, get_time_diff(data->start_time), coder_id);
	pthread_mutex_unlock(&data->print);
}

void	codexion_sleep(int ms, t_data *data)
{
	int	ms_waited;
	ssize_t	expires_at;

	ms_waited = 0;
	expires_at = get_time() + ms;
	while (get_time() <= expires_at && data->exit == 0)
		usleep(1000);
}

struct timespec	get_target_timespec(int ms)
{
	struct timeval	tv;
	struct timespec	ts;

	gettimeofday(&tv, NULL);
	ts.tv_sec = tv.tv_sec + (ms / 1000);
	ts.tv_nsec = (tv.tv_usec * 1000) + ((ms % 1000) * 1000000);
	if (ts.tv_nsec >= 1000000000)
	{
		ts.tv_sec += ts.tv_nsec / 1000000000;
		ts.tv_nsec = ts.tv_nsec % 1000000000;
	}
	return (ts);
}
