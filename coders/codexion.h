/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:37:07 by equentin          #+#    #+#             */
/*   Updated: 2026/04/08 16:43:06 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include "coders.h"
# include "dongles.h"
# include "parsing.h"
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_coder	t_coder;
typedef struct s_dongle	t_dongle;

typedef struct s_data
{
	t_coder				*coders;
	t_dongle			*dongles;
	t_parsed			*parsed;
	ssize_t				start_time;
	pthread_mutex_t		print;
}						t_data;

#endif
