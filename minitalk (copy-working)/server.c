/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:11:30 by dramos-j          #+#    #+#             */
/*   Updated: 2024/10/12 15:37:50 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>

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
		if (g_len == 0)
			g_len = -1;
		temp_len = 0;
		bit = 0;
	}
}

char	*last_c(char *str, int j)
{
	str[j] = '\0';
	ft_printf("%s\n", str);
	free(str);
	str = NULL;
	return (str);
}

void	handler(int signum)
{
	static char	c = 0;
	static int	bit = 0;
	static int	j = 0;
	static char	*str = NULL;

	if (!str && g_len > 0)
		str = ft_calloc(g_len + 1, sizeof(char));
	if (signum == SIGUSR1)
		c = c << 1 | 1;
	else
		c = (c << 1);
	bit++;
	if (bit == 8 && g_len > 0)
	{
		if (c == '\0')
		{
			str = last_c(str, j);
			g_len = 0;
			j = 0;
		}
		else
			str[j++] = c;
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
	while (1)
	{
		if (g_len == 0)
		{
			signal(SIGUSR1, handler_len);
			signal(SIGUSR2, handler_len);
		}
		else
		{
			signal(SIGUSR1, handler);
			signal(SIGUSR2, handler);
		}
	}
}
