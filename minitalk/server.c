/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:11:30 by dramos-j          #+#    #+#             */
/*   Updated: 2024/10/05 18:59:18 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	len = 0;

void	handler_len(int signum)
{
	static int	c = 0;
	static int	i = 0;

	if (signum == SIGUSR1)
		c |= 1 << i;
	i++;
	if (i == 32)
	{
		if (c != '\0')
			len++;
		c = 0;
		i = 0;
	}
}

void	handler(int signum)
{
	static char	c = 0;
	static int	i = 0;
	static int	j = 0;
	static char	*str = NULL;

	if (!str && len > 0)
	{
		str = malloc(len + 1);
		if (!str)
			exit(1);
	}
	if (signum == SIGUSR1)
		c |= 1 << i;
	i++;
	if (i == 32)
	{
		str[j++] = c;
		if (c == '\0')
		{
			str[j] = '\0';
			ft_printf("%s\n", str);
			free(str);
			str = NULL;
			len = 0;
			j = 0;
		}
		c = 0;
		i = 0;
	}
}

int	main(void)
{
	ft_printf("PID: %d\n", getpid());
	while (1)
	{
		if (len == 0)
		{
			signal(SIGUSR1, handler_len);
			signal(SIGUSR2, handler_len);
		}
		else
		{
			signal(SIGUSR1, handler);
			signal(SIGUSR2, handler);
		}
		pause();
	}
}
