/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:15:35 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/23 23:52:28 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_child_process(t_list *final_list, int pipe_ends[2], char **envp, t_infos *infos)
{
	char	*path;
	char	**strs;
	char	**splited_paths;

	signal(SIGQUIT, SIG_DFL);
	strs = final_list->commands;
	first_errno_and_open_heredocs(final_list, strs);
	first_check_for_inout_output_files(final_list, pipe_ends);
	if (is_builtin(final_list) == 1)
		execute_builtin(strs, infos);
	else
	{
		splited_paths = get_envpath(envp);
		path = get_command_path(splited_paths, strs);
		if (!path)
			exit(127);
		execve(path, strs, envp);
	}
	exit(EXIT_SUCCESS);
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
		execute_builtin(strs, infos);
	else
	{
		splited_paths = get_envpath(envp);
		path = get_command_path(splited_paths, strs);
		if (!path)
			exit(127);
		execve(path, strs, envp);
	}
	exit(EXIT_SUCCESS);
}

void	inter_process(t_list *final_list, int pipe_ends[2], char **envp, t_infos *infos)
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
		execute_builtin(strs, infos);
	else
	{
		splited_paths = get_envpath(envp);
		path = get_command_path(splited_paths, strs);
		if (!path)
			exit(127);
		execve(path, strs, envp);
	}
	exit(EXIT_SUCCESS);
}

void my_wait_all(pid_t pid, int pipe_ends[2], int size, t_infos *infos)
{
	(void)pid;
	int		i;
	
	i = 0;
	close(pipe_ends[0]);
	close(pipe_ends[1]);
	
	while (i < size)
	{
		waitpid(infos->pids[i], &g_exit_status, 0);
		i++;
	}
	if (WIFEXITED(g_exit_status))
		g_exit_status =  WEXITSTATUS(g_exit_status);
}

void execute_multiple_cmds(t_list *final_list, char **envp, t_infos *infos)
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
		redirect_process(infos->help.pipe_ends);
		tmp = tmp->next;
		infos->help.i++;
	}
	dup2(infos->std_out, STDOUT_FILENO);
	dup2(infos->std_in, STDIN_FILENO);
	my_wait_all(infos->help.pid, infos->help.pipe_ends, infos->help.size, infos);
}
