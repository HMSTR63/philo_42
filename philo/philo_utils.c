/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 03:15:41 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/23 05:56:29 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ascii_to_int(const char *str)
{
	unsigned long long	res;
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
		res = (res * 10) + (str[i++] - '0');
		if (sign == 1 && res > (unsigned long long)INT_MAX)
			return (-1);
		if (sign == -1 && res > (unsigned long long)INT_MAX + 1)
			return (0);
	}
	return ((int)res * sign);
}

int	ft_usleep(t_users *p, size_t ms)
{
	size_t	s;

	s = get_time();
	while ((get_time() - s) < ms)
	{
		if (ft_user_dead(p))
			return (1);
		usleep(500);
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
	static int	f;

	pthread_mutex_lock(p->print_mutex);
	rolex = get_time() - p->infos->light_out;
	if (!ft_user_dead(p) && f == 0)
		printf("%zu %d %s\n", rolex, p_id, s);
	if (ft_strcmp(s, "died") == 0)
		f = 1;
	pthread_mutex_unlock(p->print_mutex);
}

void	ft_print_died(char *s, t_users *p, int p_id)
{
	static int	f;

	pthread_mutex_lock(p->print_mutex);
	if (!ft_user_dead(p) && f == 0)
		printf("%zu %d %s\n", p->infos->check_tm, p_id, s);
	if (ft_strcmp(s, "died") == 0)
		f = 1;
	pthread_mutex_unlock(p->print_mutex);
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
