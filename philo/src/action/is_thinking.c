/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_thinking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:30:18 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/23 16:37:25 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int	is_thinking(t_philosopher *philo)
{
	if (check_simulation_stop(philo))
		return (1);
	print_status(philo, "is thinking");
	usleep(500);
	while (take_fork(philo->left_fork))
	{
		if (check_philo_died(philo))
			return (1);
		//usleep(200);
	}
	while (take_fork(philo->right_fork))
	{
		if (check_philo_died(philo))
			return (1);
		//usleep(200);
	}

	if (check_philo_died(philo))
		return (1);
	print_status(philo, "has taken a fork");
	print_status(philo, "has taken a fork");
	return (0);
}
