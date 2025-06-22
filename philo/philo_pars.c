/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 03:09:05 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/21 21:37:26 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	space_fund(char **v)
{
	int	h;
	int	m;
	int	fund_int;

	h = 1;
	while (v[h])
	{
		m = 0;
		fund_int = 0;
		while (v[h][m])
		{
			if (is_digit(v[h][m]) && !is_digit(v[h][m + 1]))
				fund_int++;
			m++;
		}
		if (fund_int > 1)
			return (1);
		h++;
	}
	return (0);
}

static int	is_int(char **v)
{
	int	h;
	int	m;

	h = 1;
	while (v[h])
	{
		m = 0;
		while (v[h][m])
		{
			if (!is_digit(v[h][m]) && v[h][m] != '+'
				&& !is_white_space(v[h][m]))
				return (1);
			if (!is_digit(v[h][m]) && v[h][m] == '+'
				&& !is_digit(v[h][m + 1]))
				return (1);
			m++;
		}
		h++;
	}
	return (0);
}

static int	is_empty(char **v)
{
	int	h;

	h = 1;
	while (v[h])
	{
		if (v[h][0] == '\0')
			return (1);
		h++;
	}
	return (0);
}

static int	is_valid_input(char **v, t_info *infos)
{
	if (space_fund(v))
	{
		infos->error_message = ERR_SPACES;
		return (1); // message
	}
	if (is_int(v))
	{
		infos->error_message = ERR_NOT_INT;
		return (1);
	} 
	if (is_empty(v))
	{
		infos->error_message = ERR_EMPTY;
		return (1); // message
	}
	return (0);
}

int	checker(t_info *infos, char **v)
{
	if (is_valid_input(v, infos))
		return (1); // message

	infos->user_count = ascii_to_int(v[1]);
	infos->time_to_die = ascii_to_int(v[2]);
	infos->time_to_eat = ascii_to_int(v[3]);
	infos->time_to_sleep = ascii_to_int(v[4]);
	infos->meals_to_eat = -1;
	if (v[5])
		infos->meals_to_eat = ascii_to_int(v[5]);
	if (infos->time_to_die < 1
		|| infos->time_to_eat < 1 || infos->time_to_sleep < 1
		|| (v[5] && infos->meals_to_eat <= 0))
	{
		infos->error_message = ERR_INVALID;
		return (1);
	}
	return (0);
}
