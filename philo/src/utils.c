/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:22:26 by tjooris           #+#    #+#             */
/*   Updated: 2025/03/26 15:09:30 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void	print_status(t_philosopher *philo, char *message)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("[%ld] Philosopher %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
}
int	my_usleep(long time, t_table	*table)
{
	long i;

	i = 0;
	while (i < time)
	{
		usleep(1000);
		pthread_mutex_lock(&table->status_simulation);
		if (table->stop_simulation)
			return (0);
		pthread_mutex_unlock(&table->status_simulation);
		i++;
	}
}