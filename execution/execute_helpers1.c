/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:08:24 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/23 22:08:42 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void open_heredoc_if_found(t_list *final_list, t_infos *infos, char **strs)
{

	if (final_list->delims != NULL)
	{
		open_heredoc_file(final_list, infos);
		if (final_list->in_fd == -2)
			final_list->in_fd = open(get_last_heredoc_filename(final_list), O_RDONLY);
		if (!strs[0])
			exit(EXIT_SUCCESS);
	}
}

void check_for_inout_output_files(int fd_in, int fd_out)
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
