/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:31:48 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/25 11:15:23 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void	report_death(t_philosopher	*philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->status_simulation);
    philo->status = DEAD;
	if (table->stop_simulation == 0)
		print_status(philo);
	table->stop_simulation = 1;
	pthread_mutex_unlock(&table->status_simulation);
}

int	check_philo_status(t_philosopher *philo)
{
	time_t	now;

	now = get_current_time_ms();
	if (now - philo->last_meal_time >= philo->time_to_die)
		return (0);
	return (1);
}

int check_simulation_stop(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->status_simulation);
	if (philo->table->stop_simulation == 1)
	{
		pthread_mutex_unlock(&philo->table->status_simulation);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->status_simulation);
	return (0);
}

int	check_philo_died(t_philosopher	*philo)
{
	if (check_simulation_stop(philo))
		return (1);
	if (!check_philo_status(philo))
	{
		report_death(philo);
		return (1);
	}
	return (0);
}
