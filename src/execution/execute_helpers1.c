/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:08:24 by arabiai           #+#    #+#             */
/*   Updated: 2023/04/02 02:34:11 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_infile_outfile_errors(t_list *final_list)
{
	if ((final_list->out_file && !ft_strcmp(final_list->out_file, "")))
	{
		ft_printf(2, "minishell: :ambiguous redirect\n");
		return (1);
	}
	else if (final_list->_errno != 0)
	{	
		if (final_list->in_fd == -1)
			ft_printf(2, "minishell: %s: %s\n", final_list->in_file,
				strerror(final_list->_errno));
		else if (final_list->out_fd == -1)
			ft_printf(2, "minishell: %s: %s\n", final_list->out_file,
				strerror(final_list->_errno));
		g_g.g_exit_status = EXIT_FAILURE;
		return (1);
	}
	return (0);
}

void	execute_simple_cmd(t_list *final_list, char **envp, t_infos *infos)
{
	pid_t	pid;

	g_g.g_heredoc_cmd = -2;
	pid = fork();
	if (pid == 0)
		child_process_for_one_cmd(final_list, envp, infos);
	close(final_list->in_fd);
	close(final_list->out_fd);
	waitpid(pid, &g_g.g_exit_status, 0);
	if (WIFEXITED(g_g.g_exit_status))
		g_g.g_exit_status = WEXITSTATUS(g_g.g_exit_status);
	else
		handle_execve_signal_errors(g_g.g_exit_status);
	g_g.g_heredoc_cmd = 0;
}

void	handle_heredoc(t_list *final_list, t_infos *infos)
{
	pid_t	pid;

	pid = fork();
	g_g.g_heredoc_cmd = -2;
	if (pid == 0)
	{
		if (final_list->delims)
			open_heredoc_file(final_list, infos);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &g_g.g_exit_status, 0);
	g_g.g_exit_status = WEXITSTATUS(g_g.g_exit_status);
	if (g_g.g_exit_status == EXIT_FAILURE)
		g_g.g_heredoc_cmd = -2;
	else
		g_g.g_heredoc_cmd = -1;
}

void	check_for_inout_output_files(int fd_in, int fd_out)
{	
	if (fd_in != -2)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != -2)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}
