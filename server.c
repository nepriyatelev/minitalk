/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:51:23 by modysseu          #+#    #+#             */
/*   Updated: 2021/11/25 14:43:49 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

static void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
	}
	else
	{
		if (n < 0)
		{
			n = -n;
			write(1, "-", 1);
		}
		if (n > 9)
		{
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
		else
		{
			n += 48;
			write(1, &n, 1);
		}
	}
}

static void	signal_handler(int signal, siginfo_t *siginfo, void *context)
{
	static int				i = 0;
	static pid_t			pid = 0;
	static unsigned char	ch = 0;

	(void)context;
	if (pid != siginfo->si_pid)
	{
		i = 0;
		ch = 0;
		pid = siginfo->si_pid;
	}
	if (signal == SIGUSR1)
		ch |= 0x01 << i;
	i++;
	if (i == 8)
	{
		write(1, &ch, 1);
		i = 0;
		ch = 0;
	}
	usleep(200);
	if (kill(pid, SIGUSR1) == -1)
		write(1, "Error! Invalid signal!\n", 24);
}

int	main(void)
{
	struct sigaction	sigac;

	write(1, "PID: ", 5);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sigac.sa_flags = SA_SIGINFO;
	sigac.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sigac, 0);
	sigaction(SIGUSR2, &sigac, 0);
	while (1)
		pause();
	return (0);
}
