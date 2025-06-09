/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 03:15:41 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/07 03:43:43 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ascii_to_int(const char *str)
{
	long	res;
	int		stor;
	int		i;
	int		sign;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] && is_digit(str[i]))
	{
		stor = res;
		res = (res * 10) + (str[i++] - '0');
		if (stor != (res / 10) && sign == 1)
			return (-1);
		if (stor != (res / 10) && sign == -1)
			return (0);
	}
	return (res * sign);
} 

int	ft_usleep(t_users *p, size_t ms)
{
	size_t	s;

	s = get_time();
	while ((get_time() - s) < ms)
	{
		if (ft_user_dead(p))
			return (1);
		usleep(400);
	}
	return (0);
}

size_t		get_time(void)
{
	struct timeval	tva;

	if (gettimeofday(&tva, NULL) == -1)
		return (-1);
	return (tva.tv_sec * 1000 + tva.tv_usec / 1000);
}

void	ft_print_act(char *s, t_users *p, int p_id)
{
	size_t	rolex;

	pthread_mutex_lock(p->print_mutex);
	rolex = get_time() - p->infos->light_out;
	if (!ft_user_dead(p))
		printf("%zu %d %s\n", rolex, p_id, s);
	pthread_mutex_unlock(p->print_mutex);
}
