/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_thinking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:30:18 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/25 16:41:42 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int	is_thinking(t_philosopher *philo)
{
	if (check_simulation_stop(philo))
		return (1);
	print_status(philo);
	usleep(300);
	if (fork_lock(philo))
		return (1);
	if (check_philo_died(philo))
		return (1);
	philo->status = TAKEN_FORKS;
	print_status(philo);
	philo->status = EAT;
	return (0);
}
