# philo_42

		infos->users[h].l_fork = &infos->forks[h];
		if (h == 0)
			infos->users[h].r_fork = &infos->forks[infos->user_count - 1];
		else
			infos->users[h].r_fork = &infos->forks[h - 1];
