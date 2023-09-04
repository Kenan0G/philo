/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:37:15 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/05 00:40:35 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>


///////  STRUCTURES  //////////////////////////////////////////////////////////////


// liste chainée qui a dans chaque element un thread qui correspond a un philo
typedef struct s_philo
{
	pthread_mutex_t	access;
	pthread_t		philo;
	struct s_philo	*next;
	struct timeval	time;
	int				time_to_sleep;
	int				time_to_die;
	int				time_to_eat;
	int				nb_philo;
	int				rotate;
	int				i;
	struct s_data	*data;
}					t_philo;


// structure avec les mutex pour les forks, pour les print,
// pour check si un philo est mort et pour modifier la variable rotate
typedef struct s_data
{
	pthread_mutex_t	mutex_rotate;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*fork;
	pthread_mutex_t	death;
	struct timeval	start;
	int				rotation_done;
	int				gameover;
	int				np;
	int				rm;
}					t_data;


///////  PROTOTYPES  //////////////////////////////////////////////////////////////


//------check_args.c---------------------------------------------------------------

int					check_args(int ac, char **av);

//------cleaning.c-----------------------------------------------------------------

int					free_philo(t_philo *philo, int size);

//------death.c--------------------------------------------------------------------

int					join_death(t_philo *philo);
int					check_death(t_philo *philo);

//------eat_sleep.c----------------------------------------------------------------

void				philo_eat(t_data *data, t_philo *philo);
void				last_philo_eat(t_data *data, t_philo *philo);
void				philo_sleep(t_data *data, int time);
int					one_philo(t_philo *philo, int ac, char **av);

//------routine.c------------------------------------------------------------------

int					init_threads(t_philo *philo);
void				*routine(void *param);

//------utils_2.c------------------------------------------------------------------

long int			update_time(struct timeval start);
long int			convert_time(struct timeval time);

//------utils.c--------------------------------------------------------------------

int					ft_atoi(const char *str);
void				print(t_data *data, int philo, int etat, struct timeval time);
t_philo				*ft_lst_last(t_philo *lst);
int					is_gameover(t_data *data);
int					get_rotate_value(t_data *data, int nb_philo);

#endif