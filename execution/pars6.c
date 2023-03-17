/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:23:00 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/17 19:56:43 by arabiai          ###   ########.fr       */
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
		(*head)->out_fd = open(file_name, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	else if ((*head)->prev->type == append)
		(*head)->out_fd = open(file_name, O_WRONLY|O_CREAT|O_APPEND, 0644);
	if ((*head)->out_fd == -1)
		return ((*temp)->_errno = errno, 1);
	else
	{
		// if ((*temp)->out_file)
		// 	free((*temp)->out_file);
		(*temp)->out_file = file_name;
	}
	return (0);
}
int	open_files(t_list **head, t_list **temp)
{
	char	*file_name;

	file_name = (*head)->content;
	if ((*head)->prev->type == in_redir)
	{
		(*head)->in_fd = open(file_name, O_RDONLY);
		if ((*head)->in_fd == -1)
			return ((*temp)->_errno = errno, 1);
		else
		{
			// if ((*temp)->in_file)
			// free((*temp)->in_file);
			(*temp)->in_file = file_name;
		}
	}
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

void	get_node(t_list **head, t_list **final)
{
	t_list	*temp;
	char	*tmp2;
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
	temp->commands  = split_string(temp->content);
	tmp2 = temp->content;
	char **tmp3 = ft_split(tmp2, ' ');
	temp->content = tmp3[0];
	free(tmp2);
	// free_all(tmp3);
	while (*temp->commands)
	{
		printf("command :{%s}\n", *temp->commands);
		temp->commands++;
	}
	printf("*--------------------*\n");
	ft_lstadd_back(final, temp);
}

t_list	*create_final_list(t_list **head)
{
	t_list  *final;
	int		count;

	final = NULL;
	count = count_commands(*head);
	printf("count :%d\n", count);
	while (count--)
		get_node(head, &final);
	return (final);
}
