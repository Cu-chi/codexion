/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:47:38 by equentin          #+#    #+#             */
/*   Updated: 2026/04/08 11:14:29 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
#include "coders/codexion.h"
#include "coders/dongles.h"

void	*init_coders(t_data *data)
{
	int	i;
	int	left_dongle_index;
	int	right_dongle_index;
    int one_coder;

	i = 0;
    one_coder = data->parsed->number_of_coders == 1;
	left_dongle_index = data->parsed->number_of_coders - 1 + one_coder;
	right_dongle_index = 0;
	data->coders = malloc(sizeof(t_coder) * data->parsed->number_of_coders);
	if (data->coders == NULL)
		return (NULL);
	while (i < data->parsed->number_of_coders)
	{
		data->coders[i].id = i + 1;
		data->coders[i].dongle_left = &data->dongles[left_dongle_index];
		data->coders[i].dongle_right = &data->dongles[right_dongle_index];
		left_dongle_index++;
		right_dongle_index++;
		if (left_dongle_index >= data->parsed->number_of_coders)
			left_dongle_index = 0;
		i++;
	}
	return (data->coders);
}
