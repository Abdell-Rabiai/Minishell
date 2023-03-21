/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:08:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/21 21:41:39 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*temp function */

void    print_list(t_list *list, bool flag)
{
    t_list    *current;

    current = list;
    int i = -1;
    printf("After tokenisation: of str\n");
    while (current)
    {
        i = 0;
        printf("*-------------------------------*\n");
        printf("{content:%s}\n", current->content);
        printf("{type:%d}\n", current->type);
        printf("{in_fd:%d}\n", current->in_fd);
        printf("{out_fd:%d}\n", current->out_fd);
        printf("{in_file:%s}\n", current->in_file);
        printf("{out_file:%s}\n", current->out_file);
        printf("{_errno:%d / %s}\n", current->_errno, strerror(current->_errno));
        printf("{delims:%p}\n", current->delims);
        if (flag)
        {
            if (current->delims)
			{
                while (current->delims[i].delimiter != NULL)
				{
                    printf("(delim :%d: %s)\n", i, current->delims[i].delimiter);
                    printf("(delim :%d: file :%s)\n", i, current->delims[i].tmp_file);
					i++;
				}
				
			}
            
        }
        if (current->commands)
        {
            int j = -1;
            while (current->commands[++j])
                printf("commands[%d] = [%s]\n", j, current->commands[j]);
        }
        if (current->next)
            printf("->");
        current = current->next;
    }
}

t_type	what_type(char *cmd)
{
	if (!ft_strncmp(cmd, "|", 1))
		return (Pipe);
	else if (ft_strlen(cmd) > 1 && !ft_strncmp(cmd, "<<", 2))
		return (here_doc);
	else if (ft_strlen(cmd) > 1 && !ft_strncmp(cmd, ">>", 2))
		return (append);
	else if (!ft_strncmp(cmd, "<", 1))
		return (in_redir);
	else if (!ft_strncmp(cmd, ">", 1))
		return (trunc);
	return (word);
}

void	assign_type(t_list *command)
{
	char	*cmd;
	t_list	*temp;

	temp = command;
	while (temp)
	{
		cmd = temp->content;
		temp->type = what_type(cmd);
		if (temp->prev && temp->type == word && temp->prev->type == in_redir)
			temp->type = in_file;
		else if (temp->prev && temp->type == word && temp->prev->type == trunc)
			temp->type = tr_out_file;
		else if (temp->prev && temp->type == word && temp->prev->type == append)
			temp->type = app_out_file;
		else if (temp->prev && temp->type == word
			&& temp->prev->type == here_doc)
			temp->type = delimiter;
		temp = temp->next;
	}
}

void	init(bool *d_q, bool *s_q, int *i, int *j)
{
	*i = 0;
	*j = 0;
	*d_q = false;
	*s_q = false;
}

void	remove_instant_quotes(char *str)
{
	int		i;
	bool	s_quote;
	bool	d_quote;
	int		j;

	init(&d_quote, &s_quote, &i, &j);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (!s_quote && str[i + 1] && str[i + 1] == str[i] && !d_quote)
				i += 2;
			else
			{
				str[j++] = str[i++];
				if (str[i] == '\'')
					s_quote = !s_quote;
				else
					d_quote = !d_quote;
			}
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

