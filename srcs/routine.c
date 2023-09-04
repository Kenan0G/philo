/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:13:33 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/04 23:46:12 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// créé un thread pour un philo et initialise le mutex sur les fourchettes ainsi que access
int	init_threads(t_philo *philo)
{
	int	ret;

	pthread_mutex_init(&(philo->access), NULL);
	pthread_mutex_init(&(philo->data->fork[philo->i - 1]), NULL);
	gettimeofday(&(philo->time), NULL);
	ret = pthread_create(&(philo->philo), NULL, routine, (void *)philo);
	return (ret);
}

// la routine que les philo vont suivre une fois la premiere fourchette debloquée
void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	pthread_mutex_lock(&(philo->data->mutex_print));
	pthread_mutex_unlock(&(philo->data->mutex_print));
	if (philo->i % 2 == 0)
		usleep((philo->time_to_eat / 2) * 1000);
	while (philo->rotate != 0 && is_gameover(philo->data) == 0)
	{
		if (philo->i == philo->nb_philo)
			last_philo_eat(philo->data, philo);
		else
			philo_eat(philo->data, philo);
		if (philo->rotate == 0)
		{
			pthread_mutex_lock(&(philo->data->mutex_rotate));
			philo->data->rotation_done++;
			pthread_mutex_unlock(&(philo->data->mutex_rotate));
		}
		if (philo->rotate != 0)
			print(philo->data, philo->i, 1, philo->data->start);
	}
	return (NULL);
}
