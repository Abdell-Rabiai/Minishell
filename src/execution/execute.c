/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:39:26 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/25 22:44:12 by arabiai          ###   ########.fr       */
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
	strs = final_list->commands;
	if (final_list->_errno != 0)
		ft_printf(2, "minishell: %s:\n", strerror(final_list->_errno));
	open_heredoc_if_found(final_list, infos, strs);
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
	str = node->commands[0];
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

void	execute_builtin(char **strs, t_infos *infos, t_list *final_list, pid_t pid)
{
	int	i;

	i = 0;
	signal(SIGQUIT, SIG_DFL);
	check_for_inout_output_files(final_list->in_fd, final_list->out_fd);
	if (!strs || !strs[0])
	{
		free_all(strs);
		return ;
	}
	if (!ft_strcmp(strs[0], "echo"))
		my_echo(strs);
	else if (!ft_strcmp(strs[0], "cd"))
		my_cd(strs, infos);
	else if (!ft_strcmp(strs[0], "pwd"))
		my_pwd(infos);
	else if (!ft_strcmp(strs[0], "export"))
		my_export(strs, infos);
	else if (!ft_strcmp(strs[0], "unset"))
		my_unset(strs, infos);
	else if (!ft_strcmp(strs[0], "env"))
		my_env(infos);
	else if (!ft_strcmp(strs[0], "exit"))
		my_exit(strs, pid);
}

void	execute_one_cmd(t_list *final_list, char **envp, t_infos *infos)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (final_list->out_file && !ft_strcmp(final_list->out_file, ""))
	{
		ft_printf(2, "minishell: :ambiguous redirect\n");
		return ;
	}
	else if (final_list->_errno != 0)
	{	
		ft_printf(2, "minishell: %s:\n", strerror(final_list->_errno));
		g_g.g_exit_status = EXIT_FAILURE;
		return ;
	}
	if (is_builtin(final_list) == 1 && !final_list->delims)
	{
		execute_builtin(final_list->commands, infos, final_list, 1);
		if (g_g.g_exit_status != EXIT_FAILURE)
			g_g.g_exit_status = EXIT_SUCCESS;
	}
	else
	{	
		g_g.g_heredoc_cmd = -2;
		pid = fork();
		if (pid == 0)
			child_process_for_one_cmd(final_list, envp, infos);
		waitpid(pid, &g_g.g_exit_status, 0);
		if (WIFEXITED(g_g.g_exit_status))
			g_g.g_exit_status = WEXITSTATUS(g_g.g_exit_status);
		else
			handle_execve_signal_errors(g_g.g_exit_status);
		g_g.g_heredoc_cmd = 0;
	}
	signal(SIGINT, handle_kill);
	signal(SIGQUIT, SIG_IGN);
}

void	execute(t_list *final_list, t_infos *infos)
{
	char	**envp;

	infos->pids = malloc(sizeof(pid_t) * ft_lstsize(final_list));
	if (!final_list)
		return ;
	infos->std_in = dup(STDIN_FILENO);
	infos->std_out = dup(STDOUT_FILENO);
	envp = copy_envp_into_array(infos);
	if (ft_lstsize(final_list) == 1)
		execute_one_cmd(final_list, envp, infos);
	else
	{
		handle_multiple_here_docs(final_list, infos);
		if (g_g.g_heredoc_cmd == -1)
			execute_multiple_cmds(final_list, envp, infos);
		g_g.g_heredoc_cmd = 0;
	}
	dup2(infos->std_out, STDOUT_FILENO);
	dup2(infos->std_in, STDIN_FILENO);
	unlink_heredoc_files(final_list);
	ft_free_envp_array(envp);
	free(infos->pids);
}