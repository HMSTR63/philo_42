/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 05:33:23 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/28 01:55:43 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	compleat_eat(t_users *p, pthread_mutex_t *first_fork,
	pthread_mutex_t *second_fork)
{
	if (ft_user_dead(p))
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	ft_print_act("has taken a fork", p, p->id);
	pthread_mutex_lock(p->meal_mutex);
	p->eat = 1;
	p->last_meal = get_time();
	p->meals_eaten++;
	ft_print_act("is eating", p, p->id);
	pthread_mutex_unlock(p->meal_mutex);
	ft_usleep(p, p->infos->time_to_eat);
	pthread_mutex_lock(p->meal_mutex);
	p->eat = 0;
	pthread_mutex_unlock(p->meal_mutex);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	ft_user_eat(t_users *p)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = p->l_fork;
	second_fork = p->r_fork;
	if (user_done_eating(p) || ft_user_dead(p))
		return ;
	if (p->id % 2 == 0)
	{
		first_fork = p->r_fork;
		second_fork = p->l_fork;
	}
	else
	{
		first_fork = p->l_fork;
		second_fork = p->r_fork;
	}
	pthread_mutex_lock(first_fork);
	if (ft_user_dead(p))
		return ((void)pthread_mutex_unlock(first_fork));
	ft_print_act("has taken a fork", p, p->id);
	pthread_mutex_lock(second_fork);
	compleat_eat(p, first_fork, second_fork);
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
