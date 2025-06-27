/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sleeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:30:57 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/27 13:01:15 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int	is_sleeping(t_philosopher *philo)
{
	if (check_philo_died(philo))
		return (1);
	print(philo);
	philo->status = THINK;
	if (my_usleep(philo, philo->time_to_sleep))
		return (1);
	return (0);
}
