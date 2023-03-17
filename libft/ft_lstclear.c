/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:06:07 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/15 12:30:22 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*curr;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	curr = *lst;
	while (curr)
	{
		next = curr->next;
		free(curr->content);
		// free_all(curr->commands);
		free(curr);
		curr = next;
	}
	*lst = NULL;
}
