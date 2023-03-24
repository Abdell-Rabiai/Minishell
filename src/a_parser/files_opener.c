/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:23:00 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/21 21:40:09 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(t_list **node, int to_free)
{
	t_list	*temp;
	int		i;

	i = -1;
	temp = (*node)->next;
	if ((*node)->content && to_free)
		free((*node)->content);
	free((*node));
	(*node) = temp;
}

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
	if ((*temp)->out_fd != -2 && !(*temp)->_errno)
		close((*temp)->out_fd);
	if ((*head)->type == tr_out_file && !(*temp)->_errno)
		(*temp)->out_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if ((*head)->type == app_out_file && !(*temp)->_errno)
		(*temp)->out_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*temp)->out_fd == -1 && !(*temp)->_errno)
		return (free((*temp)->out_file)
			, (*temp)->out_file = file_name, (*temp)->_errno = errno, 1);
	if (!(*temp)->_errno)
	{
		if ((*temp)->out_file)
			free((*temp)->out_file);
		(*temp)->out_file = file_name;
	}
	else
		free(file_name);
	return (0);
}

int	open_files(t_list **head, t_list **temp)
{
	char	*file_name;

	file_name = (*head)->content;
	remove_quotes(file_name);
	if ((*head)->type == in_file)
	{
		if ((*temp)->in_fd != -2 && !(*temp)->_errno)
			close((*temp)->in_fd);
		if (!(*temp)->_errno)
			(*temp)->in_fd = open(file_name, O_RDONLY);
		if ((*temp)->in_fd == -1 && !(*temp)->_errno)
			return (free((*temp)->in_file)
				, (*temp)->in_file = file_name, (*temp)->_errno = errno, 1);
		if (!(*temp)->_errno)
		{
			if ((*temp)->in_file)
				free((*temp)->in_file);
			(*temp)->in_file = file_name;
		}
		else
			free(file_name);
	}
	else
		return (open_out_file(head, temp, file_name));
	return (0);
}
