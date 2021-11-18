/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:08:17 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/18 15:08:30 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_is_philo_dead(struct timeval last_meal, t_philo *philo)
{
	struct timeval	t;
	int				ret;

	ret = gettimeofday(&t, NULL);
	if (ft_timediff(last_meal, t) > philo->ttd)
		return (1);
	return (0);
}

void	ft_philo_eat(t_philo *philo, int i)
{
	ft_lock_forks_mutex(philo, i);
	if (philo->alive)
	{
		ft_eating(philo, i);
		if (philo->alive)
		{
			if (philo->is_must_eat)
				ft_satiated(philo);
			if (philo->alive)
				ft_wait(philo->last_meal, philo->tte, philo);
		}
	}
	else
		ft_unlock_forks_mutex(philo, i);
}

void	ft_philo_sleep(t_philo *philo, int i)
{
	if (philo->alive)
	{
		ft_sleeping(philo, i);
		ft_unlock_forks_mutex(philo, i);
		if (philo->alive)
			ft_wait(philo->t, philo->tts, philo);
		if (philo->alive)
			ft_thinking(philo, i);
	}
}

void	ft_play_philo(t_philo *philo, int i)
{
	if (ft_is_philo_dead(philo->last_meal, philo))
		ft_died(philo, i);
	else if (philo->vars->nb_philos > 1 && philo->alive)
	{
		ft_philo_eat(philo, i);
		ft_philo_sleep(philo, i);
		/*philo->ret = gettimeofday(&philo->t, NULL);
		ft_wait(philo->t, ft_ttw_before_trying_to_eat(philo), philo);*/
	}
}

void	*ft_th_philo(void *p_data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)p_data;
	i = philo->id;
	philo->ret = gettimeofday(&philo->last_meal, NULL);
	philo->alive = 1;
	ft_thinking(philo, i);
	while (philo->alive)
	{
		ft_play_philo(philo, i);
	}
	return (NULL);
}
