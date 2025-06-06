/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 02:23:49 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/06 06:38:39 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int c, char **v)
{
	t_info	infos;

	if (c != 5 && c != 6)
		return (1); // write a message of usage !!!
	if (checker(&infos, v))
		return (1); // write message !!!
	setup_all(&infos);
	start_threads(&infos);
	destroy_all(&infos);
	return (0);
}
