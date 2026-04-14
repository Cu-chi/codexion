/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:07:37 by equentin          #+#    #+#             */
/*   Updated: 2026/04/14 16:08:16 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int		init_mutexes_cond(t_data *data);
void	destroy_mutex_cond(t_data *data, int destroy_lim, int cond);
