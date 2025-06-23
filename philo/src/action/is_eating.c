/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:29:24 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/23 15:12:26 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int	is_eating(t_philosopher *philo)
{
	t_table	*table = philo->table;

	if (check_philo_died(philo))
		return (1);
	print_status(philo, "is eating");
	philo->last_meal_time = get_current_time_ms();
	philo->meals_eaten++;
	if (!my_usleep(philo, table->time_to_eat))
		return (1);
	let_fork(philo);
	return (0);
}
