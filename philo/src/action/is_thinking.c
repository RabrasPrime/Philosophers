/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_thinking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:30:18 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/27 14:32:56 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int	is_thinking(t_philosopher *philo)
{
	if (check_simulation_stop(philo))
		return (1);
	print(philo);
	usleep(200);
	philo->status = TAKEN_FORKS;
	if (fork_lock(philo))
		return (1);
	if (check_philo_died(philo))
		return (1);
	philo->status = EAT;
	return (0);
}
