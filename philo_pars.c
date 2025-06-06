/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 03:09:05 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/06 03:53:46 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_input(char **v)
{
	int	h;
	int	m;

	h = 1;
	while (v[h])
	{
		m = 0;
		while (v[h][m] == ' ')
			m++;
		if (v[h][m] == '+')
			m++;
		if (!is_digit(v[h][m]))
			return (1);
		while (v[h][m])
		{
			if (!is_digit(v[h][m]) && v[h][m] != ' ')
				return (1);
			m++;
		}

		h++;
	}
	return (0);
}

int	checker(t_info *infos, char **v)
{
	if (is_valid_input(v))
		return (1); // message

	infos->user_count = ascii_to_int(v[1]);
	infos->time_to_die = ascii_to_int(v[2]);
	infos->time_to_eat = ascii_to_int(v[3]);
	infos->time_to_sleep = ascii_to_int(v[4]);
	infos->meals_to_eat = -1;
	if (v[5])
		infos->meals_to_eat = ascii_to_int(v[5]);
	if (infos->user_count < 1 || infos->time_to_die < 1
		|| infos->time_to_eat < 1 || infos->time_to_sleep < 1
		|| (v[5] && infos->meals_to_eat <= 0))
		return (1); // message
	return (0);
}
