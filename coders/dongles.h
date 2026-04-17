/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:22:35 by equentin          #+#    #+#             */
/*   Updated: 2026/04/17 11:49:53 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLES_H
# define DONGLES_H
# include "codexion.h"
# include <pthread.h>
# include <stdlib.h>

typedef struct s_data	t_data;
typedef struct s_coder	t_coder;

typedef struct s_dongle
{
	long long			available_at;
	int					in_use;
}						t_dongle;

int						init_dongles(t_data *data);
int						check_dongles_availability(t_coder *coder);
int						request_dongles(t_coder *coder);
void					release_dongles(t_coder *coder);
#endif
