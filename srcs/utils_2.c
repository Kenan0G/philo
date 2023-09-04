/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:51:47 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/04 23:56:30 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	update_time(struct timeval start)
{
	struct timeval	time;

	gettimeofday(&(time), NULL);
	return (convert_time(time) - convert_time(start));
}

long int	convert_time(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
