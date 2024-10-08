/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:43:48 by dramos-j          #+#    #+#             */
/*   Updated: 2024/10/08 17:20:11 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
			if (message[i] & (1 << j))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(500);
			j--;
		}
		i++;
	}
	message[i] = '\n';
	j = 7;
	while (j >= 0)
	{
		if (message[i] & (1 << j))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		j--;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid <= 0)
		{
			ft_printf("Invalid PID\n");
			return (1);
		}
		send_message(pid, argv[2]);
	}
	else
	{
		ft_printf("Usage: ./client [PID] [message]\n");
		return (1);
	}
	return (0);
}
