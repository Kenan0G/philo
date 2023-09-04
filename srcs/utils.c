/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:40:15 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/05 00:41:09 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// convertit un char * en int
int	ft_atoi(const char *str)
{
	int				sign;
	int				res;
	unsigned int	i;

	sign = 1;
	i = 0;
	res = 0;
	while (str[i] == 9 || (str[i] >= 10 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	i--;
	while (str[++i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		if (sign > 0 && i >= 25)
			return (-1);
		else if (sign < 0 && i >= 26)
			return (0);
	}
	return (res * sign);
}


// affiche ce que fait un philo selon la variable etat que recoit la fonction
void	print(t_data *data, int philo, int etat, struct timeval time)
{
	long int	actual_instant;

	pthread_mutex_lock(&(data->mutex_print));
	actual_instant = update_time(time);
	if (etat == 0 && get_rotate_value(data, data->np) == data->rm)
	{
		printf("%li %i died\n", actual_instant, philo);
	}
	else if (is_gameover(data) == 0)
	{
		if (etat == 1)
			printf("%ld %i is thinking\n", actual_instant, philo);
		else if (etat == 2)
			printf("%ld %i has taken a fork\n", actual_instant, philo);
		else if (etat == 3)
			printf("%ld %i is eating\n", actual_instant, philo);
		else if (etat == 4)
			printf("%ld %i is sleeping\n", actual_instant, philo);
	}
	pthread_mutex_unlock(&(data->mutex_print));
}

// avance jusqu'au dernier element de la liste chainée
t_philo	*ft_lst_last(t_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// check si un philo est mort ou pas et retourne 0 ou 1 en fonction de ca
int	is_gameover(t_data *data)
{
	int	x;

	x = 0;
	pthread_mutex_lock(&(data->death));
	if (data->gameover == 1)
		x = 1;
	pthread_mutex_unlock(&(data->death));
	return (x);
}

// check si on a fait autant de rotate que de nombre de philos
int	get_rotate_value(t_data *data, int nb_philo)
{
	int	x;

	x = 0;
	pthread_mutex_lock(&(data->mutex_rotate));
	if (data->rotation_done == nb_philo)
		x = 1;
	pthread_mutex_unlock(&(data->mutex_rotate));
	return (x);
}
