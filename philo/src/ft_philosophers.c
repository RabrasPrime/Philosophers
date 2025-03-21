/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:07:41 by tjooris           #+#    #+#             */
/*   Updated: 2025/03/21 10:46:16 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

/* ************************************************************************** */
/*                          FONCTIONS UTILITAIRES                             */
/* ************************************************************************** */

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	print_status(t_philosopher *philo, char *message)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("[%ld] Philosopher %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->table->print_lock);
}

/* ************************************************************************** */
/*                        FONCTIONS DE SIMULATION                             */
/* ************************************************************************** */

void	take_forks_and_eat(t_philosopher *philo)
{
	t_table	*table = philo->table;

	// Les philosophes pairs prennent d'abord leur fork gauche, puis droite.
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&table->forks[philo->left_fork]);
		print_status(philo, "has taken a fork 🍴 (left)");
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		print_status(philo, "has taken a fork 🍴 (right)");
	}
	// Les philosophes impairs prennent d'abord leur fork droite, puis gauche.
	else
	{
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		print_status(philo, "has taken a fork 🍴 (right)");
		pthread_mutex_lock(&table->forks[philo->left_fork]);
		print_status(philo, "has taken a fork 🍴 (left)");
	}
	print_status(philo, "is eating 🍝");
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	usleep(table->time_to_eat * 1000);
	pthread_mutex_unlock(&table->forks[philo->right_fork]);
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	print_status(philo, "is sleeping 😴");
	usleep(table->time_to_sleep * 1000);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo = (t_philosopher *)arg;

	// Si le philosophe est pair, il commence par penser pour laisser le temps à un impair de manger.
	if (philo->id % 2 == 0)
	{
		print_status(philo, "is thinking 💭");
		usleep(philo->table->time_to_eat * 1000);
	}
	// Sinon, l'impair commence directement par manger.
	else
		take_forks_and_eat(philo);
	while (!philo->table->stop_simulation)
	{
		print_status(philo, "is thinking 💭");
		take_forks_and_eat(philo);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                        MONITEUR DE SIMULATION                              */
/* ************************************************************************** */

void	monitor_simulation(t_table *table)
{
	int	i;
	int	all_full;

	while (1)
	{
		all_full = 1;
		for (i = 0; i < table->num_philosophers; i++)
		{
			// Vérifier la condition de mort
			if ((get_time_in_ms() - table->philosophers[i].last_meal_time) > table->time_to_die)
			{
				print_status(&table->philosophers[i], "died 💀");
				table->stop_simulation = 1;
				return ;
			}
			// Si le nombre de repas requis est défini, vérifier que chaque philosophe l'a atteint.
			if (table->must_eat_count != -1 && table->philosophers[i].meals_eaten < table->must_eat_count)
				all_full = 0;
		}
		// Si tous les philosophes ont mangé le nombre requis, on arrête la simulation.
		if (table->must_eat_count != -1 && all_full)
		{
			table->stop_simulation = 1;
			return ;
		}
		usleep(1000);
	}
}

/* ************************************************************************** */
/*                        INITIALISATION ET LANCEMENT                         */
/* ************************************************************************** */

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (NULL);
	}
	table = malloc(sizeof(t_table));
	table->num_philosophers = atoi(argv[1]);
	table->time_to_die = atol(argv[2]);
	table->time_to_eat = atol(argv[3]);
	table->time_to_sleep = atol(argv[4]);
	table->must_eat_count = (argc == 6) ? atoi(argv[5]) : -1;
	table->stop_simulation = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
	table->philosophers = malloc(sizeof(t_philosopher) * table->num_philosophers);
	pthread_mutex_init(&table->print_lock, NULL);
	table->start_time = get_time_in_ms();
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		table->philosophers[i].id = i;
		table->philosophers[i].left_fork = i;
		table->philosophers[i].right_fork = (i + 1) % table->num_philosophers;
		table->philosophers[i].last_meal_time = get_time_in_ms();
		table->philosophers[i].meals_eaten = 0;
		table->philosophers[i].table = table;
		i++;
	}
	return (table);
}

void	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_create(&table->philosophers[i].thread, NULL, philosopher_routine, &table->philosophers[i]);
		i++;
	}
	monitor_simulation(table);
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
}

/* ************************************************************************** */
/*                                 MAIN                                       */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;

	table = init_table(argc, argv);
	if (!table)
		return (1);
	start_simulation(table);
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	free(table->forks);
	free(table->philosophers);
	free(table);
	return (0);
}
