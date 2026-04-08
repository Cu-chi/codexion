/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:35:35 by equentin          #+#    #+#             */
/*   Updated: 2026/04/08 13:59:16 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H
# include "dongles.h"

typedef struct s_coder
{
	int			id;
	size_t		last_compile;
	int			number_of_compilation;
	t_dongle	*dongle_left;
	t_dongle	*dongle_right;
}				t_coder;

void			*init_coders(t_data *data);
#endif
