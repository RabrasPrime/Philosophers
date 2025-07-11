/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:58:26 by tjooris           #+#    #+#             */
/*   Updated: 2025/07/04 12:34:58 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int	check_nb_philo(t_philosopher *philo)
{
	int	i;

	pthread_mutex_lock(&philo->table->status_simulation);
	i = philo->table->num_philosophers;
	pthread_mutex_unlock(&philo->table->status_simulation);
	return (i);
}

void	init_value(t_table *table, int nb_philo, int eat_count)
{
	table->num_philosophers = nb_philo;
	table->must_eat_count = eat_count;
	table->have_eaten = 0;
	table->stop_simulation = 0;
	table->start_time = get_current_time_ms();
}

int	join_philo(t_table *table, int num_philo_join)
{
	int	i;

	i = 0;
	while (i < num_philo_join)
	{
		if (pthread_join(table->philosophers[i].thread, NULL))
			return (0);
		i++;
	}
	return (1);
}
