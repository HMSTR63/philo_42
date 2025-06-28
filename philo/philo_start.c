/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 04:38:02 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/28 02:01:05 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_info *infos)
{
	pthread_t	monitor;
	int			created;

	created = 0;
	pthread_mutex_lock(&infos->print_mutex);
	if (pthread_create(&monitor, NULL, &monitor_routine, &infos->users) != 0)
		return (pthread_mutex_unlock(&infos->print_mutex), 1);
	if (start_user_threads(infos, &created) != 0)
	{
		pthread_mutex_unlock(&infos->print_mutex);
		pthread_join(monitor, NULL);
		return (1);
	}
	infos->light_out = get_time();
	pthread_mutex_unlock(&infos->print_mutex);
	if (pthread_join(monitor, NULL))
		return (1);
	if (join_user_threads(infos, created) != 0)
		return (1);
	return (0);
}

int	ft_user_dead(t_users *p)
{
	int	rip;

	pthread_mutex_lock(p->dead_mutex);
	rip = p->infos->rip_f;
	pthread_mutex_unlock(p->dead_mutex);
	return (rip);
}

static void	handle_single_user(t_users *p)
{
	pthread_mutex_lock(p->r_fork);
	ft_print_act("has taken a fork", p, p->id);
	ft_usleep(p, p->infos->time_to_die);
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_lock(p->dead_mutex);
	if (!p->infos->rip_f)
	{
		p->infos->rip_f = 1;
		ft_print_act("died", p, p->id);
	}
	pthread_mutex_unlock(p->dead_mutex);
}

void	*user_routine(void *hmstr)
{
	t_users	*p;

	p = (t_users *)hmstr;
	if (p->id % 2 == 0)
		ft_usleep(p, p->infos->time_to_eat / 2);
	if (p->infos->user_count == 1)
	{
		handle_single_user(p);
		return (NULL);
	}
	while (!ft_user_dead(p) && !user_done_eating(p))
	{
		ft_user_eat(p);
		ft_user_sleep(p);
		ft_user_think(p);
	}
	return (NULL);
}

void	*monitor_routine(void *hmstr)
{
	t_users	*p;

	p = (t_users *)hmstr;
	while (63)
	{
		if (check_user_dead(p) == 1 || check_users_eat(p) == 1)
			break ;
		usleep(1000);
	}
	return (NULL);
}
