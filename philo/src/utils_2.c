/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:58:26 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/27 14:16:12 by tjooris          ###   ########.fr       */
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
}
