/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:11:49 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/24 17:40:45 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_errno_and_open_heredocs(t_list *final_list, char **strs)
{
	if (final_list->_errno != 0)
	{
		ft_printf(2, "minishell: %s:\n", strerror(final_list->_errno));
		exit(EXIT_FAILURE);
	}
	if (final_list->delims != NULL)
	{
		if (final_list->in_fd == -2)
			final_list->in_fd = open(get_last_heredoc_filename(final_list),
					O_RDONLY);
		dup2(final_list->in_fd, STDIN_FILENO);
		if (!strs[0])
			exit(EXIT_SUCCESS);
	}
}

void	first_check_for_inout_output_files(t_list *final_list, int pipe_ends[2])
{
	if (final_list->out_fd != -2)
	{
		dup2(final_list->out_fd, STDOUT_FILENO);
		close(final_list->out_fd);
	}
	else
	{
		close(pipe_ends[0]);
		dup2(pipe_ends[1], STDOUT_FILENO);
	}
	if (final_list->in_fd != -2)
	{
		dup2(final_list->in_fd, STDIN_FILENO);
		close(final_list->in_fd);
	}
}

void	last_check_for_input_output_files(t_list *final_list, t_infos *infos)
{
	if (final_list->in_fd != -2)
	{
		dup2(final_list->in_fd, STDIN_FILENO);
		close(final_list->in_fd);
	}
	if (final_list->out_fd == -2)
		dup2(infos->std_out, STDOUT_FILENO);
	else
	{
		dup2(final_list->out_fd, STDOUT_FILENO);
		close(final_list->out_fd);
	}
}
