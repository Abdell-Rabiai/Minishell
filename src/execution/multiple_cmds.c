/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:15:35 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/25 22:34:42 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_child_process(t_list *final_list, int pipe_ends[2]
	, char **envp, t_infos *infos)
{
	char	*path;
	char	**strs;
	char	**splited_paths;

	signal(SIGQUIT, SIG_DFL);
	strs = final_list->commands;
	first_errno_and_open_heredocs(final_list, strs);
	first_check_for_inout_output_files(final_list, pipe_ends);
	if (is_builtin(final_list) == 1)
		execute_builtin(strs, infos, final_list, 0);
	else
	{
		splited_paths = get_envpath(envp);
		path = get_command_path(splited_paths, strs);
		if (!path)
			exit(127);
		execve(path, strs, envp);
	}
	if (g_g.g_exit_status != EXIT_FAILURE)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

void	last_child_process(t_list *final_list, char **envp, t_infos *infos)
{
	char	*path;
	char	**strs;
	char	**splited_paths;

	signal(SIGQUIT, SIG_DFL);
	strs = final_list->commands;
	first_errno_and_open_heredocs(final_list, strs);
	last_check_for_input_output_files(final_list, infos);
	if (is_builtin(final_list) == 1)
		execute_builtin(strs, infos, final_list, 0);
	else
	{
		splited_paths = get_envpath(envp);
		path = get_command_path(splited_paths, strs);
		if (!path)
			exit(127);
		execve(path, strs, envp);
	}
	if (g_g.g_exit_status != EXIT_FAILURE)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

void	inter_process(t_list *final_list, int pipe_ends[2]
	, char **envp, t_infos *infos)
{
	char	*path;
	char	**strs;
	char	**splited_paths;

	signal(SIGQUIT, SIG_DFL);
	strs = final_list->commands;
	if (!strs[0])
		exit(EXIT_SUCCESS);
	first_errno_and_open_heredocs(final_list, strs);
	first_check_for_inout_output_files(final_list, pipe_ends);
	if (is_builtin(final_list) == 1)
		execute_builtin(strs, infos, final_list, 0);
	else
	{
		splited_paths = get_envpath(envp);
		path = get_command_path(splited_paths, strs);
		if (!path)
			exit(127);
		execve(path, strs, envp);
	}
	if (g_g.g_exit_status != EXIT_FAILURE)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

void	my_wait_all(int pipe_ends[2], int size, t_infos *infos)
{
	int	i;

	i = 0;
	close(pipe_ends[0]);
	close(pipe_ends[1]);
	while (i < size)
	{
		waitpid(infos->pids[i], &g_g.g_exit_status, 0);
		i++;
	}
	if (WIFEXITED(g_g.g_exit_status))
		g_g.g_exit_status = WEXITSTATUS(g_g.g_exit_status);
	else if (WIFSIGNALED(g_g.g_exit_status))
		handle_execve_signal_errors(g_g.g_exit_status);
	signal(SIGINT, handle_kill);
	signal(SIGQUIT, SIG_IGN);
}

void	execute_multiple_cmds(t_list *final_list, char **envp, t_infos *infos)
{
	t_list	*tmp;

	infos->help.size = ft_lstsize(final_list);
	tmp = final_list;
	infos->help.i = 0;
	while (infos->help.i < infos->help.size)
	{
		create_pipe(infos->help.pipe_ends);
		infos->help.pid = my_fork(infos, infos->help.i);
		if (infos->help.pid == 0)
		{
			if (infos->help.i == 0)
				first_child_process(tmp, infos->help.pipe_ends, envp, infos);
			else if (infos->help.i == infos->help.size - 1)
				last_child_process(tmp, envp, infos);
			else
				inter_process(tmp, infos->help.pipe_ends, envp, infos);
		}
		if (tmp->delims != NULL && !tmp->next)
			wait(NULL);
		redirect_process(infos->help.pipe_ends);
		tmp = tmp->next;
		infos->help.i++;
	}
	my_wait_all(infos->help.pipe_ends, infos->help.size, infos);
}
