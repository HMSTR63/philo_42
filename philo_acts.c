/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 05:33:23 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/06 21:05:59 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_user_eat(t_users *p)
{
	// if (p->l_fork < p->r_fork)
	// {
	// 	pthread_mutex_lock(p->l_fork);
	// 	ft_print_act("has taken a fork", p, p->id);
	// 	if (p->rip || *p->rip == 1)
	// 	{
	// 		ft_usleep(p, p->infos->time_to_eat);
	// 		pthread_mutex_unlock(p->r_fork);
	// 		return ;
	// 	}
	// 	pthread_mutex_lock(p->r_fork);
	// 	ft_print_act("has taken a fork", p, p->id);
	// }
	// else
	// {
	// 	pthread_mutex_lock(p->r_fork);
	// 	ft_print_act("has taken a fork", p, p->id);
	// 	if (p->infos->user_count == 1)
	// 	{
	// 		ft_usleep(p, p->infos->time_to_eat);
	// 		pthread_mutex_unlock(p->r_fork);
	// 		return ;
	// 	}
	// 	pthread_mutex_lock(p->l_fork);
	// 	ft_print_act("has taken a fork", p, p->id);
	// }
	pthread_mutex_lock(p->r_fork);
	ft_print_act("has taken a fork", p, p->id);
	pthread_mutex_lock(p->l_fork);
	ft_print_act("has taken a fork", p, p->id);
	p->eat = 1;
	ft_print_act("is eating", p, p->id);
	pthread_mutex_lock(p->meal_mutex);
	p->last_meal = get_time();
	p->meals_eaten++;
	pthread_mutex_unlock(p->meal_mutex);
	ft_usleep(p, p->infos->time_to_eat);
	p->eat = 0;
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}

void	ft_user_sleep(t_users *p)
{
	ft_print_act("is sleeping", p, p->id);
	ft_usleep(p, p->infos->time_to_sleep);
}

void	ft_user_think(t_users *p)
{
	ft_print_act("is thinking", p, p->id);
}
