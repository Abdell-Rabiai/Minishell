/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:08:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/24 23:07:17 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*temp function */

void	finish_node(t_list **final, t_list *temp, int i)
{
	if (i == -1)
	{
		free(temp->delims);
		temp->delims = NULL;
	}
	else
		temp->delims[++i].delimiter = NULL;
	remove_quotes_node(&temp);
	ft_lstadd_back(final, temp);
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
