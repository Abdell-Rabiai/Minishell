/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 02:09:48 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/24 20:37:45 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle2(int status)
{
	if (WTERMSIG(status) == SIGTERM)
		ft_printf(2, "Terminated: %d\n", SIGTERM);
	else if (WTERMSIG(status) == SIGTRAP)
		ft_printf(2, "Trace/breakpoint trap: %d\n", SIGTRAP);
	else if (WTERMSIG(status) == SIGSYS)
		ft_printf(2, "Bad system call: %d\n", SIGSYS);
	else if (WTERMSIG(status) == SIGXCPU)
		ft_printf(2, "CPU time limit exceeded: %d\n", SIGXCPU);
	else if (WTERMSIG(status) == SIGXFSZ)
		ft_printf(2, "File size limit exceeded: %d\n", SIGXFSZ);
	else if (WTERMSIG(status) == SIGPIPE)
		ft_printf(2, "Broken pipe: %d\n", SIGPIPE);
	else if (WTERMSIG(status) == SIGALRM)
		ft_printf(2, "Alarm clock: %d\n", SIGALRM);
	else if (WTERMSIG(status) == SIGVTALRM)
		ft_printf(2, "Virtual alarm clock: %d\n", SIGVTALRM);
	else if (WTERMSIG(status) == SIGPROF)
		ft_printf(2, "Profiling alarm clock: %d\n", SIGPROF);
}

void	handle_execve_signal_errors(int status)
{
	if (WIFEXITED(status))
		g_g.g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_g.g_exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGSEGV)
			ft_printf(2, "Segmentation fault: %d\n", SIGSEGV);
		else if (WTERMSIG(status) == SIGABRT)
			ft_printf(2, "Abort: %d\n", SIGABRT);
		else if (WTERMSIG(status) == SIGFPE)
			ft_printf(2, "Floating point exception: %d\n", SIGFPE);
		else if (WTERMSIG(status) == SIGILL)
			ft_printf(2, "Illegal instruction: %d\n", SIGILL);
		else if (WTERMSIG(status) == SIGBUS)
			ft_printf(2, "Bus error: %d\n", SIGBUS);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_printf(2, "Quit: %d\n", SIGQUIT);
		else if (WTERMSIG(status) == SIGKILL)
			ft_printf(2, "Killed: %d\n", SIGKILL);
		handle2(status);
	}
}
