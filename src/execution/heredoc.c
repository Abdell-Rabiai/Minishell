/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:37:37 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/28 22:37:31 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	loop(char *lim, int type, t_infos *infos, int fd)
{
	char	*str;

	while (1)
	{
		str = readline("Here>> ");
		if (!str)
			break ;
		if (!ft_strcmp(str, lim))
		{
			free(str);
			break ;
		}
		if (type == delimiter)
			str = check_and_expand_heredoc(str, infos);
		ft_printf(fd, str);
		ft_printf(fd, "\n");
		free(str);
	}
}

void	open_heredoc_file(t_list *final_list, t_infos *infos)
{
	int		fd;
	int		i;
	char	*lim;
	t_list	*current;

	signal(SIGINT, &handle_signal);
	current = final_list;
	if (!current)
		return ;
	i = -1;
	while (current->delims[++i].delimiter)
	{
		fd = open(current->delims[i].tmp_file, O_CREAT | O_RDWR | O_TRUNC, 777);
		if (fd < 0)
		{
			perror("minishell: open");
			exit(EXIT_FAILURE);
		}
		lim = current->delims[i].delimiter;
		loop(lim, current->delims[i].type, infos, fd);
	}
	close(fd);
}
