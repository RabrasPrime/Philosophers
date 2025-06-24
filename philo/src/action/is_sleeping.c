/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sleeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:30:57 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/24 15:25:35 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int	is_sleeping(t_philosopher *philo)
{
	t_table	*table = philo->table;

	if (check_philo_died(philo))
		return (1);
    if (check_philo_died(philo))
      return (1);
	print_status(philo);
	philo->status = THINK;
	if (my_usleep(philo, table->time_to_sleep))
		return (1);
	return (0);
}
