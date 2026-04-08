/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:18:25 by equentin          #+#    #+#             */
/*   Updated: 2026/04/08 17:02:44 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/codexion.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

ssize_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

ssize_t	get_time_diff(ssize_t start_time)
{
	return (get_time() - start_time);
}

void	print_lock(t_data *data, char *fmt, int coder_id)
{
	pthread_mutex_lock(&data->print);
	printf(fmt, get_time_diff(data->start_time), coder_id);
	pthread_mutex_unlock(&data->print);
}
