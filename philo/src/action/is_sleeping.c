/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sleeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:30:57 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/25 08:35:45 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int	is_sleeping(t_philosopher *philo)
{

	if (check_philo_died(philo))
		return (1);
    if (check_philo_died(philo))
      return (1);
	print_status(philo);
	philo->status = THINK;
	if (my_usleep(philo, philo->time_to_sleep))
		return (1);
	return (0);
}
