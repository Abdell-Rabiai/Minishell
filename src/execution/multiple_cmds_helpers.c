/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmds_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:30:00 by arabiai           #+#    #+#             */
/*   Updated: 2023/06/14 18:31:41 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_process(int pipe_ends[2], t_list *tmp)
{
	close(tmp->out_fd);
	close(tmp->in_fd);
	close(pipe_ends[1]);
	dup2(pipe_ends[0], STDIN_FILENO);
	close(pipe_ends[0]);
}

void	create_pipe(t_infos *info, int *i)
{
	if (pipe(info->help.pipe_ends) == -1)
	{
		perror("minishell: pipe:");
		*i = info->help.size;
		return ;
	}
}

pid_t	my_fork(t_infos *info, int *i)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork:");
		*i = info->help.size;
		return (-1);
	}
	info->pids[*i] = pid;
	return (pid);
}
