/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:55:34 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/04 23:38:54 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// free la liste philo et la structure data par la meme occasion
int	free_philo(t_philo *philo, int size)
{
	t_philo	*p_temp;
	int		i;

	p_temp = NULL;
	i = -1;
	if (philo && philo->data && philo->data->fork)
		free(philo->data->fork);
	if (philo && philo->data)
		free(philo->data);
	while (++i < size)
	{
		p_temp = philo->next;
		if (philo)
		{
			free(philo);
			philo = NULL;
		}
		philo = p_temp;
	}
	return (0);
}
