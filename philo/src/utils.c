/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:22:26 by tjooris           #+#    #+#             */
/*   Updated: 2025/04/03 12:29:42 by tjooris          ###   ########.fr       */
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
int	my_usleep(t_table *table, time_t time)
{
	time_t i;

	i = get_time_in_ms() + time;
	while (get_time_in_ms() < time)
	{
		usleep(1000);
		pthread_mutex_lock(&table->status_simulation);
		if (table->stop_simulation)
			return (0);
		pthread_mutex_unlock(&table->status_simulation);
	}
	return (1);
}
int my_atoi(char *str)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while(str[i])
	{
		i++;
	}
}
