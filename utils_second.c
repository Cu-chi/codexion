/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 09:33:52 by equentin          #+#    #+#             */
/*   Updated: 2026/04/14 13:00:31 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
#include "coders/codexion.h"
#include "coders/utils.h"
#include <pthread.h>

void	lock_ordered(t_coder *coder)
{
	if (coder->dongle_left > coder->dongle_right)
	{
		pthread_mutex_lock(&coder->dongle_left->mutex);
		pthread_mutex_lock(&coder->dongle_right->mutex);
		return ;
	}
	pthread_mutex_lock(&coder->dongle_right->mutex);
	pthread_mutex_lock(&coder->dongle_left->mutex);
}

int	check_exit(t_data *data)
{
	int	exited;

	pthread_mutex_lock(&data->exit_mutex);
	exited = data->exit;
	pthread_mutex_unlock(&data->exit_mutex);
	return (exited);
}

int	check_finished(t_data *data)
{
	int	finished;

	pthread_mutex_lock(&data->finished_mutex);
	finished = data->coder_finished >= data->parsed->number_of_coders;
	pthread_mutex_unlock(&data->finished_mutex);
	return (finished);
}

int	has_burned_out(t_coder *coder, t_parsed *parsed)
{
	int	coder_burned_out;

	coder_burned_out = 0;
	pthread_mutex_lock(&coder->mutex);
	if (coder->number_of_compilation < parsed->number_of_compiles_required
		&& get_time_diff(coder->last_compile) > parsed->time_to_burnout)
		coder_burned_out = 1;
	pthread_mutex_unlock(&coder->mutex);
	return (coder_burned_out);
}
