/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 04:38:02 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/24 18:25:35 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_info *infos)
{
	pthread_t	monitor;

	pthread_mutex_lock(&infos->print_mutex);
	if (pthread_create(&monitor, NULL, &monitor_routine, &infos->users) != 0)
		return (destroy_all(infos), 1);
	if (start_user_threads(infos) != 0)
		return (1);
	infos->light_out = get_time();
	pthread_mutex_unlock(&infos->print_mutex);
	if (pthread_join(monitor, NULL) != 0)
		return (destroy_all(infos), 1);
	if (join_user_threads(infos) != 0)
		return (1);
	return (0);
}

int	ft_user_dead(t_users *p)
{
	pthread_mutex_lock(p->dead_mutex);
	if (*p->rip == 1)
		return (pthread_mutex_unlock(p->dead_mutex), 1);
	pthread_mutex_unlock(p->dead_mutex);
	return (0);
}

void	*user_routine(void *hmstr)
{
	t_users	*p;

	p = (t_users *)hmstr;
	pthread_mutex_lock(&p->infos->print_mutex);
	pthread_mutex_unlock(&p->infos->print_mutex);
	if (p->infos->user_count == 1)
	{
		pthread_mutex_lock(p->r_fork);
		ft_print_act("has taken a fork", p, p->id);
		ft_usleep(p, p->infos->time_to_die);
		ft_print_act("died", p, p->id);
		pthread_mutex_unlock(p->r_fork);
		*p->rip = 1;
		return (hmstr);
	}
	if (p->id % 2 == 0)
		ft_usleep(p, p->infos->time_to_eat / 2);
	while (!ft_user_dead(p))
	{
		ft_user_eat(p);
		ft_user_sleep(p);
		ft_user_think(p);
	}
	return (hmstr);
}

void	*monitor_routine(void *hmstr)
{
	t_users	*p;

	p = (t_users *)hmstr;
	while (63)
		if (check_user_dead(p) == 1 || check_users_eat(p) == 1)
			break ;
	return (hmstr);
}
