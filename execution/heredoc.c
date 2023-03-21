/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:37:37 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/21 19:26:17 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_last_heredoc_filename(t_list *final_list)
{
	int i;
	t_list *current;
	
	current = final_list;
	if (!current)
		return (NULL);
	i = 0;
	while (current->delims[i].delimiter)
		i++;
	return (current->delims[i - 1].tmp_file);
}

void open_heredoc_file(t_list *final_list)
{
    int fd;
    int i;
    char *str;
    char *lim;
    t_list *current;
    
    current = final_list;
    if (!current)
        return ;
    i = -1;
    while (current->delims[++i].delimiter)
    {
    	fd = open(current->delims[i].tmp_file, O_CREAT | O_RDWR | O_TRUNC, 777);
    	if (fd < 0)
        	perror("minishell: open");
        lim = current->delims[i].delimiter;
        while (1)
        {
            str = readline("Tabi3aGnang >> ");
            if (!str)
                break ;
            if (!ft_strcmp(str, lim))
            {
                free(str);
                break ;
            }
            ft_printf(fd, str);
            ft_printf(fd, "\n");
            free(str);
        }
        // free(lim);
    }
    close(fd);
}

void handle_multiple_here_docs(t_list *final_list)
{
    int i;
    t_list *current;

    current = final_list;
    i = -1;
    while (current)
    {
        if (current->delims)
            open_heredoc_file(current);
        current = current->next;
    }
}