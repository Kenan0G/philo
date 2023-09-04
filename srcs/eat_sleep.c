/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:51:29 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/05 00:40:49 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// fait manger philo et met a jour philo->time ainsi que philo->rotate puis fait dormir philo
void	philo_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->fork[philo->i - 1]));
	print(data, philo->i, 2, philo->data->start);
	pthread_mutex_lock(&(data->fork[philo->i]));
	print(data, philo->i, 2, philo->data->start);
	print(data, philo->i, 3, philo->data->start);
	pthread_mutex_lock(&(philo->access));
	gettimeofday(&(philo->time), NULL);
	pthread_mutex_unlock(&(philo->access));
	philo_sleep(data, philo->time_to_eat);
	philo->rotate--;
	pthread_mutex_unlock(&(data->fork[philo->i - 1]));
	pthread_mutex_unlock(&(data->fork[philo->i]));
	if (philo->rotate != 0)
	{
		print(data, philo->i, 4, philo->data->start);
		philo_sleep(data, philo->time_to_sleep);
	}
}

// fait la meme que philo eat mais prends les fourchettes 0 et i - 1 au lieu de i - 1 et i
void	last_philo_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->fork[0]));
	print(data, philo->i, 2, philo->data->start);
	pthread_mutex_lock(&(data->fork[philo->i - 1]));
	print(data, philo->i, 2, philo->data->start);
	print(data, philo->i, 3, philo->data->start);
	pthread_mutex_lock(&(philo->access));
	gettimeofday(&(philo->time), NULL);
	pthread_mutex_unlock(&(philo->access));
	philo_sleep(data, philo->time_to_eat);
	philo->rotate--;
	pthread_mutex_unlock(&(data->fork[0]));
	pthread_mutex_unlock(&(data->fork[philo->i - 1]));
	if (philo->rotate != 0)
	{
		print(data, philo->i, 4, philo->data->start);
		philo_sleep(data, philo->time_to_sleep);
	}
}

// utilise usleep durant time temps
void	philo_sleep(t_data *data, int time)
{
	struct timeval	start;
	struct timeval	current;
	int				i;

	i = 0;
	gettimeofday(&(current), NULL);
	gettimeofday(&(start), NULL);
	while (++i && convert_time(start) + time > convert_time(current))
	{
		usleep(200);
		gettimeofday(&(current), NULL);
		if (i % 20 == 0 && is_gameover(data) == 1)
			break ;
	}
}

// gere lorsqu'il y a qu'un seul philo, il n'a pas de dexieme fourchette donc meurt apres en avoir ramassé une
int	one_philo(t_philo *philo, int ac, char **av)
{
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (free_philo(philo, philo->nb_philo));
	printf("0 1 has taken a fork\n");
	usleep(philo->time_to_die * 1000);
	printf("%i 1 died\n", philo->time_to_die);
	return (free_philo(philo, philo->nb_philo));
}
