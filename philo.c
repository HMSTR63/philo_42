/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 02:23:49 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/06 22:53:23 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(int error_code)
{
	if (error_code == ERR_USAGE)
	{
		write(2, "Error: Invalid number of arguments.\n", 36);
		print_usage();
	}
	else if (error_code == ERR_SPACES)
		write(2, "Error: Too many spaces in input.\n", 34);
	else if (error_code == ERR_NOT_INT)
		write(2, "Error: Input must be an integer.\n", 33);
	else if (error_code == ERR_EMPTY)
		write(2, "Error: Input cannot be empty.\n", 30);
	else if (error_code == ERR_INVALID)
		write(2, "Error: Invalid input.\n", 22);
}

void	print_usage(void)
{
	write(1, "Usage: ./philo <num_philosophers> <time_to_die> ", 49);
	write(1, "<time_to_eat> <time_to_sleep> [meals_required]\n", 47);

	write(1, "\nArguments:\n", 12);
	write(1, "  <num_philosophers>: Number of philosophers (1-200).\n", 54);
	write(1, "  <time_to_die>: Time (ms) until a philosopher dies if not eating.\n", 67);
	write(1, "  <time_to_eat>: Time (ms) a philosopher spends eating.\n", 56);
	write(1, "  <time_to_sleep>: Time (ms) a philosopher spends sleeping.\n", 60);
	write(1, "  [meals_required]: Optional. Number of meals before simulation ends.\n", 69);

	write(1, "\nExample:\n", 10);
	write(1, "  ./philo 4 800 200 200 3\n", 25);
	write(1, "  Starts 4 philosophers: each has 800ms to live, 200ms to eat,\n", 63);
	write(1, "  200ms to sleep, and eats 3 meals in total.\n", 46);
}



int	main(int c, char **v)
{
	t_info	infos;

	if (c != 5 && c != 6)
	{
		print_error(ERR_USAGE);
		return (1);
	}
	if (checker(&infos, v))
	{
		print_error(infos.error_message);
		print_usage();
		return (1);
	}
	setup_all(&infos);
	start_threads(&infos);
	destroy_all(&infos);
	return (0);
}
