/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:22:26 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/05 00:40:15 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

// initiatlise la liste chainée philo
t_philo	*init_philo(t_data *data, int av_5, t_philo *philo, char **av)
{
	t_philo	*p_temp;
	int		i;

	i = 0;
	while (++i <= ft_atoi(av[1]))
	{
		p_temp = malloc(sizeof(t_philo));
		if (!p_temp)
			return (NULL);
		p_temp->nb_philo = ft_atoi(av[1]);
		p_temp->time_to_die = ft_atoi(av[2]);
		p_temp->time_to_eat = ft_atoi(av[3]);
		p_temp->time_to_sleep = ft_atoi(av[4]);
		p_temp->rotate = av_5;
		p_temp->data = data;
		p_temp->next = NULL;
		p_temp->i = i;
		if (philo != NULL)
			ft_lst_last((philo))->next = p_temp;
		else
			philo = p_temp;
		if (i != 1 && i == p_temp->nb_philo)
			ft_lst_last(philo)->next = philo;
	}
	return (philo);
}

// initiatlise la structure data
t_philo	*data_init(t_data **data, char **av, int ac)
{
	int		rot;
	t_philo	*philo;

	rot = -1;
	philo = NULL;
	if (ac == 6)
		rot = ft_atoi(av[5]);
	(*data) = calloc(sizeof(t_data), 1);
	if (!data)
		return (NULL);
	if (ac == 6)
		(*data)->rm = ft_atoi(av[5]);
	(*data)->np = ft_atoi(av[1]);
	(*data)->rotation_done = 0;
	(*data)->gameover = 0;
	pthread_mutex_init(&((*data)->death), NULL);
	pthread_mutex_init(&((*data)->mutex_rotate), NULL);
	pthread_mutex_init(&((*data)->mutex_print), NULL);
	(*data)->fork = malloc(sizeof(pthread_mutex_t) * (ft_atoi(av[1])));
	if (!(*data)->fork)
		return (NULL);
	philo = init_philo(*data, rot, philo, av);
	return (philo);
}


int main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;
	t_philo	*p_temp;
	int		i;

	while ((ac == 5 || ac == 6) && check_args(ac, av))
	{
		i = -1;
		philo = data_init(&data, av, ac);
		p_temp = philo;
		if (philo->nb_philo == 1)
			return (one_philo(philo, ac, av));
		pthread_mutex_lock(&(data->mutex_print));
		while (++i < philo->nb_philo)
		{
			if (init_threads(philo) == -1)
				return (free_philo(philo, philo->nb_philo));
			philo = philo->next;
		}
		return (gettimeofday(&((philo)->data->start), NULL),
			pthread_mutex_unlock(&(data->mutex_print)), join_death(p_temp));
	}
	printf("Invalid args\n");
}
