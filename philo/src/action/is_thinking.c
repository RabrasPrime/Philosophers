/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_thinking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:30:18 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/24 15:21:46 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int	is_thinking(t_philosopher *philo)
{
	if (check_simulation_stop(philo))
		return (1);
	print_status(philo);
	while (take_fork(philo->left_fork))
	{
		if (check_philo_died(philo))
			return (1);
        usleep(100);
	}
	while (take_fork(philo->right_fork))
	{
		if (check_philo_died(philo))
			return (1);
		usleep(100);
	}
    if (check_philo_died(philo))
      return (1);
    philo->status = TAKEN_FORKS;
	print_status(philo);
    philo->status = EAT;
	return (0);
}
