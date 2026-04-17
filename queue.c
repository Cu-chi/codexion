/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:56:52 by equentin          #+#    #+#             */
/*   Updated: 2026/04/17 11:55:08 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/codexion.h"
#include "coders/queue.h"
#include <string.h>

int	enqueue(t_data *data, t_coder *coder)
{
	t_queue	*queue;
	t_queue	*enqueued;

	enqueued = malloc(sizeof(t_queue));
	if (enqueued == NULL)
		return (0);
	memset(enqueued, 0, sizeof(t_queue));
	enqueued->coder = coder;
	if (data->queue == NULL)
	{
		data->queue = enqueued;
		return (1);
	}
	queue = data->queue;
	while (queue && queue->next != NULL)
		queue = queue->next;
	queue->next = enqueued;
	return (1);
}

void	dequeue(t_data *data, t_coder *coder)
{
	t_queue	*current;
	t_queue	*previous;

	current = data->queue;
	previous = 0;
	while (current != NULL)
	{
		if (current->coder == coder)
		{
			if (previous)
				previous->next = current->next;
			else
				data->queue = current->next;
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

int	is_priority_holder(t_data *data, t_coder *coder)
{
	t_queue	*queue;

	queue = data->queue;
	if (queue == NULL)
		return (0);
	while (queue != NULL)
	{
		if (queue->coder == coder)
			return (1);
		if (queue->coder->dongle_left == coder->dongle_right)
			return (0);
		if (queue->coder->dongle_right == coder->dongle_left)
			return (0);
		if (queue->coder->dongle_left == coder->dongle_left)
			return (0);
		if (queue->coder->dongle_right == coder->dongle_right)
			return (0);
		queue = queue->next;
	}
	return (0);
}

void	free_queue(t_queue *queue)
{
	t_queue	*current;

	while (queue)
	{
		current = queue;
		queue = current->next;
		free(current);
	}
}
