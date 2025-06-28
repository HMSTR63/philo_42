/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 04:20:54 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/28 01:30:02 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

# define MAX_USER 200

# define ERR_USAGE		1
# define ERR_SPACES		2
# define ERR_NOT_INT	3
# define ERR_EMPTY		4
# define ERR_INVALID	5

typedef struct s_users
{
	int				id;
	int				eat;
	int				meals_eaten;
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
	int				error_message;
	int				user_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	int				rip_f;
	size_t			light_out;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	forks[MAX_USER];
	t_users			users[MAX_USER];
}	t_info;

void		ft_print_died(char *s, t_users *p, int p_id);
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
int			is_white_space(char c);
void		print_error(int error_code);
void		print_usage(void);
int			ft_strcmp(const char *s1, const char *s2);
int			start_user_threads(t_info *infos, int *created);
int			join_user_threads(t_info *infos, int created);
int			user_done_eating(t_users *p);
#endif
