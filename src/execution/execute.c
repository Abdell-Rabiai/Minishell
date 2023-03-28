/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:39:26 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/28 05:00:14 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process_for_one_cmd(t_list *final_list,
	char **envp, t_infos *infos)
{
	char	*path;
	char	**splited_paths;
	char	**strs;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, handle_kill);
	strs = final_list->commands;
	first_errno_and_open_heredocs(final_list, strs);
	check_for_inout_output_files(final_list->in_fd, final_list->out_fd);
	if (is_builtin(final_list) == 1)
	{
		execute_builtin(strs, infos, final_list, 1);
		exit(EXIT_SUCCESS);
	}
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

int	is_builtin(t_list *node)
{
	char	*str;

	if (!node->commands || !node->commands[0])
		return (0);
	str = str_lower(node->commands[0]);
	if (ft_strcmp(node->commands[0], "export") == 0)
		return (1);
	if (ft_strcmp(node->commands[0], "unset") == 0)
		return (1);
	if (ft_strcmp(node->commands[0], "exit") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	return (0);
}

void	execute_builtin(char **strs, t_infos *infos, t_list *final_list,
		pid_t pid)
{
	char	*str;

	signal(SIGQUIT, SIG_DFL);
	check_for_inout_output_files(final_list->in_fd, final_list->out_fd);
	if (!strs || !strs[0])
	{
		free_all(strs);
		return ;
	}
	str = str_lower(strs[0]);
	if (!ft_strcmp(strs[0], "export"))
		my_export(strs, infos);
	else if (!ft_strcmp(strs[0], "unset"))
		my_unset(strs, infos);
	else if (!ft_strcmp(strs[0], "exit"))
		my_exit(strs, pid, infos);
	else if (!ft_strcmp(str, "echo"))
		my_echo(strs);
	else if (!ft_strcmp(str, "cd"))
		my_cd(strs, infos);
	else if (!ft_strcmp(str, "pwd"))
		my_pwd(infos);
	else if (!ft_strcmp(str, "env"))
		my_env(infos);
}

void	execute_one_cmd(t_list *final_list, char **envp, t_infos *infos)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (check_infile_outfile_errors(final_list) == 1)
		return ;
	if (is_builtin(final_list) == 1 && !final_list->delims)
	{
		execute_builtin(final_list->commands, infos, final_list, 1);
		if (g_g.g_exit_status != EXIT_FAILURE)
			g_g.g_exit_status = EXIT_SUCCESS;
	}
	else
		execute_simple_cmd(final_list, envp, infos);
	signal(SIGINT, handle_kill);
	signal(SIGQUIT, SIG_IGN);
}

void	execute(t_list *final_list, t_infos *infos)
{
	if (!final_list)
		return ;
	infos->pids = malloc(sizeof(pid_t) * ft_lstsize(final_list));
	infos->std_in = dup(STDIN_FILENO);
	infos->std_out = dup(STDOUT_FILENO);
	infos->envp = copy_envp_into_array(infos);
	if (ft_lstsize(final_list) == 1)
	{
		handle_heredoc(final_list, infos);
		if (g_g.g_heredoc_cmd == -1)
			execute_one_cmd(final_list, infos->envp, infos);
	}
	else
	{
		handle_multiple_here_docs(final_list, infos);
		if (g_g.g_heredoc_cmd == -1)
			execute_multiple_cmds(final_list, infos->envp, infos);
	}
	g_g.g_heredoc_cmd = 0;
	dup2(infos->std_out, STDOUT_FILENO);
	dup2(infos->std_in, STDIN_FILENO);
	unlink_heredoc_files(final_list);
	ft_free_envp_array(infos->envp);
	free(infos->pids);
}
