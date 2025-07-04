/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 06:10:03 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/28 01:57:11 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_white_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static int	user_dead(t_users *p, size_t time_to_die)
{
	size_t	current_time;
	size_t	check_time;
	int		eat_status;

	pthread_mutex_lock(p->meal_mutex);
	current_time = get_time();
	check_time = current_time - p->last_meal;
	eat_status = p->eat;
	pthread_mutex_unlock(p->meal_mutex);
	if (eat_status)
		return (0);
	return (check_time > (size_t)time_to_die);
}

int	check_user_dead(t_users *p)
{
	int	h;

	h = 0;
	while (h < p->infos->user_count)
	{
		if (user_dead(&p->infos->users[h], p->infos->time_to_die))
		{
			pthread_mutex_lock(&p->infos->dead_mutex);
			if (p->infos->rip_f == 0)
			{
				p->infos->rip_f = 1;
				ft_print_act("died", &p->infos->users[h],
					p->infos->users[h].id);
			}
			pthread_mutex_unlock(&p->infos->dead_mutex);
			return (1);
		}
		h++;
	}
	return (0);
}

int	check_users_eat(t_users *p)
{
	int	h;
	int	has_eaten;

	h = 0;
	has_eaten = 0;
	if (p->infos->meals_to_eat == -1)
		return (0);
	while (h < p->infos->user_count)
	{
		pthread_mutex_lock(p->infos->users[h].meal_mutex);
		if (p->infos->users[h].meals_eaten >= p->infos->meals_to_eat)
			has_eaten++;
		pthread_mutex_unlock(p->infos->users[h].meal_mutex);
		h++;
	}
	if (has_eaten == p->infos->user_count)
	{
		pthread_mutex_lock(p->dead_mutex);
		p->infos->rip_f = 1;
		pthread_mutex_unlock(p->dead_mutex);
		return (1);
	}
	return (0);
}

void	destroy_all(t_info *infos)
{
	int	h;

	h = 0;
	while (h < infos->user_count)
	{
		pthread_mutex_destroy(&infos->forks[h]);
		h++;
	}
	pthread_mutex_destroy(&infos->print_mutex);
	pthread_mutex_destroy(&infos->dead_mutex);
	pthread_mutex_destroy(&infos->meal_mutex);
}
