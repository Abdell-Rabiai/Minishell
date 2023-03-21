/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:35:45 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/21 18:12:54 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_node(t_list **head, t_list **final)
{
	t_list	*temp;
	int		i;

	temp = ft_lstnew(ft_strdup("", 0));
	i = -1;
	if (*head && (*head)->type == Pipe)
		free_node(head, 1);
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
	finish_node(final, temp, i);
}

void	remove_quotes_node(t_list **temp)
{
	int	i;
	int	in_quotes;
	int	num_tokens;

	i = -1;
	in_quotes = 0;
	num_tokens = 0;
	(*temp)->commands = split_string((*temp)->content, in_quotes, num_tokens);
		while ((*temp)->commands[++i])
			remove_quotes((*temp)->commands[i]);
	i = -1;
	if ((*temp)->delims)
	{
		while ((*temp)->delims[++i].delimiter)
			remove_quotes((*temp)->delims[i].delimiter);
	}
}

t_list	*create_final_list(t_list **head)
{
	t_list	*final;
	int		count;

	final = NULL;
	count = count_commands(*head);
	while (count--)
		get_node(head, &final);
	return (final);
}
