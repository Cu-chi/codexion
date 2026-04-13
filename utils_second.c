/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 09:33:52 by equentin          #+#    #+#             */
/*   Updated: 2026/04/13 09:54:26 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
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
