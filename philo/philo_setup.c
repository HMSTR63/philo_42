/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 03:56:16 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/28 01:29:53 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup_all(t_info *infos)
{
	int	h;

	h = -1;
	while (++h < infos->user_count)
		pthread_mutex_init(&infos->forks[h], NULL);
	infos->rip_f = 0;
	pthread_mutex_init(&infos->print_mutex, NULL);
	pthread_mutex_init(&infos->dead_mutex, NULL);
	pthread_mutex_init(&infos->meal_mutex, NULL);
	h = -1;
	while (++h < infos->user_count)
	{
		infos->users[h].id = h + 1;
		infos->users[h].eat = 0;
		infos->users[h].meals_eaten = 0;
		infos->users[h].last_meal = get_time();
		infos->users[h].l_fork = &infos->forks[h];
		infos->users[h].r_fork = &infos->forks[(h + 1) % infos->user_count];
		infos->users[h].print_mutex = &infos->print_mutex;
		infos->users[h].dead_mutex = &infos->dead_mutex;
		infos->users[h].meal_mutex = &infos->meal_mutex;
		infos->users[h].infos = infos;
	}
}
