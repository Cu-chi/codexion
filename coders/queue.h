/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:54:21 by equentin          #+#    #+#             */
/*   Updated: 2026/04/15 11:05:55 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

typedef struct s_data	t_data;
typedef struct s_coder	t_coder;

typedef struct s_queue
{
	void				*next;
	t_coder				*coder;
}						t_queue;

int						enqueue(t_data *data, t_coder *coder);
void					dequeue(t_data *data, t_coder *coder);
int						is_priority_holder(t_data *data, t_coder *coder);
void					free_queue(t_queue *queue);

#endif
