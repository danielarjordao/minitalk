/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:11:30 by dramos-j          #+#    #+#             */
/*   Updated: 2024/10/09 12:13:00 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_len = 0;

void	handler_len(int signum)
{
	static int	temp_len = 0;
	static int	bit = 0;

	if (signum == SIGUSR1)
		temp_len = (temp_len << 1) | 1;
	else
		temp_len = (temp_len << 1);
	bit++;
	if (bit == 32)
	{
		g_len = temp_len;
		ft_printf("Message length: %d\n", g_len);
		if (g_len == 0)
			g_len = -1;
		temp_len = 0;
		bit = 0;
	}
}

void	handler(int signum, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit = 0;
	static int	j = 0;
	static char	*str = NULL;

	(void)context;
	if (!str && g_len > 0)
		str = ft_calloc(g_len + 1, sizeof(char));
	if (signum == SIGUSR1)
		c = c << 1 | 1;
	else
		c = (c << 1);
	bit++;
	if (bit == 8)
	{
		if (j < g_len)
			str[j++] = c;
		if (c == '\0')
		{
			if (str)
			{
				str[j] = '\0';
				ft_printf("%s\n", str);
				free(str);
			}
			str = NULL;
			g_len = 0;
			j = 0;
		}
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_printf("Error sending signal\n");
		c = 0;
		bit = 0;
	}
}

int	main(void)
{
	int	pid;
	struct sigaction	sa_len;
	struct sigaction	sa;


	sa_len.sa_handler = handler_len;
	sa_len.sa_flags = 0;
	sigaction(SIGUSR1, &sa_len, NULL);
	sigaction(SIGUSR2, &sa_len, NULL);
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	if (pid < 0)
	{
		ft_printf("Error: getpid() failed\n");
		exit(1);
	}
	else
		ft_printf("PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
