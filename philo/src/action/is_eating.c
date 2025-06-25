/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:29:24 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/25 16:39:29 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void	check_quotta_eaten(t_philosopher *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->status_simulation);
	if (philo->meals_eaten == table->must_eat_count)
		table->have_eaten += 1;
	pthread_mutex_unlock(&table->status_simulation);
}

int	is_eating(t_philosopher *philo)
{
	if (check_philo_died(philo))
		return (1);
	print_status(philo);
	philo->last_meal_time = get_current_time_ms();
	philo->meals_eaten++;
	if (!my_usleep(philo, philo->time_to_eat))
		return (1);
	check_quotta_eaten(philo);
	let_fork(philo);
	philo->status = SLEEP;
	return (0);
}
