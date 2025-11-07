/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:11:01 by hermarti          #+#    #+#             */
/*   Updated: 2025/11/07 20:36:38 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>

typedef struct s_env	t_env;

typedef enum e_fork_type
{
	LEFT_FORK,
	RIGHT_FORK
}						t_fork_type;

typedef struct s_fork
{
	int					fork_id;
	pthread_mutex_t		fork_mutex;
}						t_fork;

typedef struct s_philo
{
	t_env				*env;
	int					philo_id;
	pthread_t			philo_thread;
	int					eat_count;
	struct timeval		time_last_eat;
	pthread_mutex_t		time_mutex;
}						t_philo;

typedef struct s_waiter
{
	pthread_t			waiter_thread;
	int					someone_died;
	int					continue_serving;
	pthread_mutex_t		any_death_check_mutex;
	pthread_mutex_t		serving_check_mutex;
}						t_waiter;

typedef struct s_env
{
	int					num_philos;
	int					death_time;
	int					eat_time;
	int					sleep_time;
	int					num_eat_times_philo;
	t_fork				**forks;
	t_philo				**philos;
	t_waiter			*waiter;
	pthread_mutex_t		print_mutex;
	struct timeval		start_time;
}						t_env;

void					init_env(t_env *env, int argc, char *argv[]);
void					init_env_threads(t_env *env);
void					destro_env_philos(t_env *env);
void					destro_env_forks(t_env *env);
void					clean_env(t_env *env);

t_philo					*create_philo(int philo_id);
void					destroy_philo(void *philo);
int						create_philo_thread(t_philo *philo);

void					philo_eat(t_env *env, t_philo *philo);
void					philo_think(t_env *env, t_philo *philo);
void					philo_sleep(t_env *env, t_philo *philo);
void					*philo_life(void *arg);
int						philo_is_dead(t_env *env, t_philo *philo);
void					print_philo_msg(t_env *env, t_philo *philo, char *msg);
int						get_elapsed_time(struct timeval start_time);

t_fork					*create_fork(int fork_id);
void					*destroy_fork(t_fork *fork);

t_waiter				*create_waiter(void);
void					*destroy_waiter(t_waiter *waiter);
void					*waiter_check_philos(void *arg);
void					waiter_give_philo_forks(t_env *env);
int						ask_waiter_for_fork(t_env *env, t_philo *philo,
							t_fork_type fork_type);
void					give_waiter_fork(t_env *env, t_philo *philo,
							t_fork_type fork_type);
int						ask_waiter_someone_died(t_env *env);
int						check_all_philos_done(t_env *env);

int						check_args(int argc, char *argv[]);

char					*ft_itoa(int n);
long					ft_atol(char *nptr);
int						ft_atoi(char *nptr);
int						ft_strlen(char *str);

int						print_error(char *erro_str);

#endif
