/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 02:23:49 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/24 23:28:29 by sojammal         ###   ########.fr       */
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
	write(1, "<time_to_eat> <time_to_sleep> [meals_required]\n", 48);
	write(1, "\nArguments:\n", 13);
	write(1, "  <num_philosophers>: Number of philosophers (1-200).\n", 55);
	write(1, "  <time_to_die>: Time (ms) until ", 34);
	write(1, "a philosopher dies if they don't eat.\n", 39);
	write(1, "  <time_to_eat>: Time (ms) a philosopher spends eating.\n", 57);
	write(1, "  <time_to_sleep>: Time (ms) ", 30);
	write(1, "a philosopher spends sleeping.\n", 32);
	write(1, "  [meals_required]: Optional. ", 31);
	write(1, "Number of meals each philosopher must eat.\n", 44);
	write(1, "\nExample:\n", 11);
	write(1, "  ./philo 4 800 200 200 3\n", 27);
	write(1, "  Starts 4 philosophers: ", 26);
	write(1, "each philosopher has 800ms to die, ", 36);
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
