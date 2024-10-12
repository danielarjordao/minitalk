/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:43:48 by dramos-j          #+#    #+#             */
/*   Updated: 2024/10/12 14:14:59 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_size(int pid, char *message)
{
	int	len;
	int	i;

	len = ft_strlen(message);
	i = 31;
	while (i >= 0)
	{
		if (len & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000);
		i--;
	}
}

void	send_message(int pid, char *message)
{
	int	i;
	int	j;

	i = 0;
	while (message[i])
	{
		j = 7;
		while (j >= 0)
		{
			if (((message[i] >> j) & 1) == 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(1000);
			j--;
		}
		i++;
	}
	j = 7;
	while (j >= 0)
	{
		kill(pid, SIGUSR2);
		usleep(100);
		j--;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid > 0)
		{
			send_size(pid, argv[2]);
			send_message(pid, argv[2]);
		}
	}
	else
		ft_printf("Usage: ./client [PID] [message]\n");
	return (0);
}
