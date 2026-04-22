/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 12:48:39 by equentin          #+#    #+#             */
/*   Updated: 2026/04/22 10:51:02 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "typedef.h"

struct					s_parsed
{
	int					number_of_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					time_to_refactor;
	int					number_of_compiles_required;
	int					dongle_cooldown;
	char				*scheduler;
};

int						parse(t_data *data, int ac, char **av);
#endif
