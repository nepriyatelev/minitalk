/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:09:50 by modysseu          #+#    #+#             */
/*   Updated: 2021/11/25 15:25:23 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

static int	ft_atoi(const char *str)
{
	unsigned int	result;
	int				sign;
	size_t			i;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i++] - '0');
	}
	if (result > 2147483648 && sign == -1)
		return (0);
	if (result > 2147483647 && sign == 1)
		return (-1);
	return (result * sign);
}

static void	signal_handler(int signal)
{
	(void)signal;
}

static void	ft_dispatch(int pid, char *message)
{
	int	bit;
	int	i;

	i = 0;
	while (message[i] != '\0')
	{
		bit = 0;
		while (bit < 8)
		{
			if ((message[i] >> bit) & 0x01)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit++;
			pause();
			usleep(160);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sigac;

	if (argc != 3)
	{
		return (write(1, "Invalid number of arguments\n", 29));
	}
	sigac.sa_handler = signal_handler;
	sigaction(SIGUSR1, &sigac, 0);
	sigaction(SIGUSR2, &sigac, 0);
	ft_dispatch(ft_atoi(argv[1]), argv[2]);
	return (0);
}
