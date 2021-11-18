/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:50:46 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/18 14:19:22 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_lock_vars_mutex(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->mutex);
}

void	ft_unlock_vars_mutex(t_philo *philo)
{
	pthread_mutex_unlock(&philo->vars->mutex);
}

void	ft_lock_forks_mutex(t_philo *philo, int i)
{
	int	j;

	j = (i + 1) % philo->vars->nb_philos;
	if (i % 2 == 0)
	{
		pthread_mutex_lock(&philo->vars->forks[j].mutex);
		if (ft_is_philo_dead(philo->last_meal, philo) && ft_play(philo))
			ft_died(philo, i);
		else
			ft_taken_a_fork(philo, i);
		if (philo->alive)
		{
			pthread_mutex_lock(&philo->vars->forks[i].mutex);
			if (ft_is_philo_dead(philo->last_meal, philo) && ft_play(philo))
			{
				ft_died(philo, i);
				pthread_mutex_unlock(&philo->vars->forks[i].mutex);
			}
			else
				ft_taken_a_fork(philo, i);
		}
		else
			pthread_mutex_unlock(&philo->vars->forks[j].mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->vars->forks[i].mutex);
		if (ft_is_philo_dead(philo->last_meal, philo) && ft_play(philo))
			ft_died(philo, i);
		else
			ft_taken_a_fork(philo, i);
		if (philo->alive)
		{
			pthread_mutex_lock(&philo->vars->forks[j].mutex);
			if (ft_is_philo_dead(philo->last_meal, philo) && ft_play(philo))
			{
				ft_died(philo, i);
				pthread_mutex_unlock(&philo->vars->forks[j].mutex);
			}
			else
				ft_taken_a_fork(philo, i);
		}
		else
			pthread_mutex_unlock(&philo->vars->forks[i].mutex);
	}
}

void	ft_unlock_forks_mutex(t_philo *philo, int i)
{
	int	j;

	j = (i + 1) % philo->vars->nb_philos;
	pthread_mutex_unlock(&philo->vars->forks[i].mutex);
	pthread_mutex_unlock(&philo->vars->forks[j].mutex);
}

int	ft_play(t_philo *philo)
{
	if (philo->alive)
	{
		ft_lock_vars_mutex(philo);
		if (philo->vars->play == 0)
		{
			ft_unlock_vars_mutex(philo);
			philo->alive = 0;
			return (0);
		}
		else
			ft_unlock_vars_mutex(philo);
	}
	else
		return (0);
	philo->ret = gettimeofday(&philo->t, NULL);
	ft_wait(philo->t, 10, philo);
	return (1);
}
