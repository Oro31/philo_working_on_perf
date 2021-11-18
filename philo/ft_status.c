/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:59:42 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/18 15:09:38 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_taken_a_fork(t_philo *philo, int i)
{
	ft_dead(philo);
	if (philo->alive)
	{
		pthread_mutex_lock(&philo->vars->write);
		philo->ret = gettimeofday(&philo->t, NULL);
		ft_printf("has taken a fork", ft_timediff(philo->i_ttmp, philo->t),
			(i + 1));
		pthread_mutex_unlock(&philo->vars->write);
	}
}

void	ft_sleeping(t_philo *philo, int i)
{
	ft_dead(philo);
	if (philo->alive)
	{
		pthread_mutex_lock(&philo->vars->write);
		philo->ret = gettimeofday(&philo->t, NULL);
		ft_printf("is sleeping", ft_timediff(philo->i_ttmp, philo->t), (i + 1));
		pthread_mutex_unlock(&philo->vars->write);
	}
}

void	ft_eating(t_philo *philo, int i)
{
	ft_dead(philo);
	if (philo->alive)
	{
		pthread_mutex_lock(&philo->vars->write);
		philo->ret = gettimeofday(&philo->last_meal, NULL);
		ft_printf("is eating", ft_timediff(philo->i_ttmp, philo->last_meal),
			(i + 1));
		pthread_mutex_unlock(&philo->vars->write);
	}
}

void	ft_thinking(t_philo *philo, int i)
{
	ft_dead(philo);
	if (philo->alive)
	{
		pthread_mutex_lock(&philo->vars->write);
		philo->ret = gettimeofday(&philo->t, NULL);
		ft_printf("is thinking", ft_timediff(philo->i_ttmp, philo->t), (i + 1));
		pthread_mutex_unlock(&philo->vars->write);
	}
}

void	ft_died(t_philo *philo, int i)
{
	ft_dead(philo);
	if (philo->alive)
	{
		pthread_mutex_lock(&philo->vars->write);
		philo->ret = gettimeofday(&philo->t, NULL);
		ft_printf("died", ft_timediff(philo->i_ttmp, philo->t), (i + 1));
		pthread_mutex_unlock(&philo->vars->write);
		philo->alive = 0;
		ft_lock_vars_mutex(philo);
		philo->vars->play = 0;
		ft_unlock_vars_mutex(philo);
	}
}
