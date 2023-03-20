/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:25:34 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/20 21:39:40 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
    fd = open("/tmp/tmpfile", O_CREAT | O_RDWR | O_TRUNC, 777);
    if (fd < 0)
        perror("minishell: open");
    while (current->delims[++i].delimiter)
    {
        lim = current->delims[i].delimiter;
        while (1)
        {
            str = readline("Tabi3a> ");
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
        free(lim);
    }
    close(fd);
}
    
void multiple_heredocs(t_list *final_list)
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
        unlink("/tmp/tmpfile");
    }
}