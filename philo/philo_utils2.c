/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:26:11 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/28 01:42:52 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_user_threads(t_info *infos, int *created)
{
	int	h;

	h = 0;
	*created = 0;
	while (h < infos->user_count)
	{
		if (pthread_create(&infos->users[h].user, NULL,
				&user_routine, &infos->users[h]) != 0)
		{
			pthread_mutex_lock(infos->users->dead_mutex);
			infos->rip_f = 1;
			pthread_mutex_unlock(infos->users->dead_mutex);
			while (--h >= 0)
				pthread_join(infos->users[h].user, NULL);
			return (1);
		}
		h++;
		(*created)++;
	}
	return (0);
}

int	join_user_threads(t_info *infos, int created)
{
	int	h;

	h = 0;
	while (h < created)
	{
		pthread_join(infos->users[h].user, NULL);
		h++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	user_done_eating(t_users *p)
{
	if (p->infos->meals_to_eat == -1)
		return (0);
	pthread_mutex_lock(p->meal_mutex);
	if (p->meals_eaten >= p->infos->meals_to_eat)
	{
		pthread_mutex_unlock(p->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(p->meal_mutex);
	return (0);
}
