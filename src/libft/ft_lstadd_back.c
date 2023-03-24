/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:53:38 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/24 23:00:17 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **list, t_list *new)
{
	t_list	*current;

	current = (*list);
	if (!new)
		return ;
	if (!(*list))
		*list = new;
	else
	{
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new;
		new->prev = current;
	}
}
