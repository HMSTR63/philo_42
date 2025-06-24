/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 05:33:23 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/24 18:20:32 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	compleat_eat(t_users *p)
{
	p->eat = 1;
	ft_print_act("is eating", p, p->id);
	pthread_mutex_lock(p->meal_mutex);
	p->last_meal = get_time();
	p->meals_eaten++;
	pthread_mutex_unlock(p->meal_mutex);
	ft_usleep(p, p->infos->time_to_eat);
	p->eat = 0;
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(p->l_fork);
}

void	ft_user_eat(t_users *p)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = p->l_fork;
	second_fork = p->r_fork;
	if (ft_user_dead(p))
		return ;
	pthread_mutex_lock(first_fork);
	if (ft_user_dead(p))
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	ft_print_act("has taken a fork", p, p->id);
	pthread_mutex_lock(second_fork);
	if (ft_user_dead(p))
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	ft_print_act("has taken a fork", p, p->id);
	compleat_eat(p);
}

void	ft_user_sleep(t_users *p)
{
	if (ft_user_dead(p))
		return ;
	ft_print_act("is sleeping", p, p->id);
	ft_usleep(p, p->infos->time_to_sleep);
}

void	ft_user_think(t_users *p)
{
	if (ft_user_dead(p))
		return ;
	ft_print_act("is thinking", p, p->id);
}
