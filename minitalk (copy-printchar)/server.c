/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:11:30 by dramos-j          #+#    #+#             */
/*   Updated: 2024/10/08 17:16:37 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signum)
{
	static char	c = 0;
	static int	bit = 0;

	if (signum == SIGUSR1)
		c = c << 1 | 1;
	else
		c = (c << 1);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", c);
		c = 0;
		bit = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	if (pid < 0)
	{
		ft_printf("Error: getpid() failed\n");
		exit(1);
	}
	else
		ft_printf("PID: %d\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
}
