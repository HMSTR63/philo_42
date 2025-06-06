/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 04:20:54 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/06 06:49:42 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

# define MAX_USER 200

typedef struct s_users
{
	int				id;
	int				eat;
	int				meals_eaten;
	int				*rip;
	size_t			last_meal;
	pthread_t		user;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*meal_mutex;
	struct s_info	*infos;
}	t_users;

typedef struct s_info
{
	int				user_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meals_to_eat;
	int				rip_f;
	size_t			light_out;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	forks[MAX_USER];
	t_users			users[MAX_USER];
}	t_info;


void		setup_all(t_info *infos);
int			start_threads(t_info *infos);
int			checker(t_info *infos, char **v);
int			is_digit(char c);
int			ascii_to_int(const char *str);
size_t		get_time(void);
int			ft_usleep(t_users *p, size_t ms);
void		ft_user_eat(t_users *p);
void		ft_user_sleep(t_users *p);
void		ft_user_think(t_users *p);
void		*monitor_routine(void *hmstr);
void		*user_routine(void *hmstr);
int			check_user_dead(t_users *p);
int			check_users_eat(t_users *p);
void		ft_print_act(char *s, t_users *p, int p_id);
void		destroy_all(t_info *infos);
int			ft_user_dead(t_users *p);
#endif
