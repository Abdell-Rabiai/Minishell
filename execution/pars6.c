/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:23:00 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/18 22:17:50 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_commands(t_list *temp)
{
	int	count;

	count = 0;
	while (temp)
	{
		if (temp->type == Pipe)
			count++;
		temp = temp->next;
	}
	return (count + 1);
}

t_type	which_delimiter(char *str)
{
	if (ft_strchr(str, '\"') || ft_strchr(str, '\''))
		return (_delimiter);
	else
		return (delimiter);
}

int	open_out_file(t_list **head, t_list **temp, char *file_name)
{
	if ((*head)->prev->type == trunc)
		(*temp)->out_fd = open(file_name, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	else if ((*head)->prev->type == append)
		(*temp)->out_fd = open(file_name, O_WRONLY|O_CREAT|O_APPEND, 0644);
	if ((*temp)->out_fd == -1)
		return ((*temp)->_errno = errno, 1);
	else
	{
		if ((*temp)->out_file)
			free((*temp)->out_file);
		(*temp)->out_file = file_name;
	}
	return (0);
}

int	open_files(t_list **head, t_list **temp)
{
	char	*file_name;

	file_name = (*head)->content;
	remove_quotes(file_name);
	if ((*head)->prev->type == in_redir)
	{
		(*temp)->in_fd = open(file_name, O_RDONLY);
		if ((*temp)->in_fd == -1)
			return ((*temp)->_errno = errno, 1);
		else
		{
			if ((*temp)->in_file)
				free((*temp)->in_file);
			(*temp)->in_file = file_name;
		}
	}
	else
        if (open_out_file(head, temp, file_name))
            return (1);
	return (0);
}

int    count_delimiter(t_list *temp)
{
	int count;

	count = 0;
	while (temp && temp->type != Pipe)
	{
		if (temp->type == delimiter)
			count++;
		temp = temp->next;
	}
	return (count + 1);
}

int	open_fill(t_list **head, t_list **temp, int i)
{
	if ((*head)->type == in_file || (*head)->type == out_file)
	{
		if (open_files(head, temp))
		{
			while ((*head) && (*head)->type != Pipe)
				(*head) = (*head)->next;
			return (-2);
		}
	}
	else if ((*head)->type == delimiter)
	{
		(*temp)->delims[++i].type = which_delimiter((*head)->content);
		(*temp)->delims[i].delimiter = (*head)->content;
	}
	if (*head)
		(*head) = (*head)->next;
	(*temp)->type = word;
	return (i);
}

// remove_quotes, string like this ls"'hello'"world , should output ls'hello'world, "hel'lo'world" should output hel'lo'world
void	remove_quotes(char *str)
{
	int	i;
	int	j;
	int	quote;

	i = -1;
	j = 0;
	quote = 0;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			else
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
	}
	str[j] = '\0';
}

void	get_node(t_list **head, t_list **final)
{
	t_list	*temp;
	int		i;

	temp = ft_lstnew(ft_strdup("", 0));
	i = -1;
	if (*head && (*head)->type == Pipe)
		(*head) = (*head)->next;
	temp->delims = malloc(count_delimiter(*head) * sizeof(t_delim));
	while ((*head) && (*head)->type != Pipe)
	{
		if ((*head)->type == word)
		{
			temp->content = ft_strjoin(temp->content, (*head)->content, 1);
			temp->content = ft_strjoin(temp->content, " ", 1);
		}
		i = open_fill(head, &temp, i);
		if (i == -2)
		{
			i = -1;
			break ;
		}
	}
	if (i == -1)
		temp->delims = NULL;
	else
		temp->delims[++i].delimiter = NULL;
	remove_quotes_node(&temp);
	ft_lstadd_back(final, temp);
}

void	remove_quotes_node(t_list **temp)
{
	int	i;

    i = -1; 
	(*temp)->commands = split_string((*temp)->content);
		while ((*temp)->commands[++i])
			remove_quotes((*temp)->commands[i]);
	// remove_quotes((*temp)->out_file);
	// remove_quotes((*temp)->in_file);
	i = -1;
	if ((*temp)->delims)
	{
		while ((*temp)->delims[++i].delimiter)
            remove_quotes((*temp)->delims[i].delimiter);
	}
}

t_list	*create_final_list(t_list **head)
{
	t_list  *final;
	int		count;

	final = NULL;
	count = count_commands(*head);
	while (count--)
		get_node(head, &final);
	return (final);
}
