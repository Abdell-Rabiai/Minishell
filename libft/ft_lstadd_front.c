/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackhole <blackhole@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:42:34 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/06 12:37:35 by blackhole        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_lstadd_front(t_list **lst, t_list *new)
// {
// 	if (!new)
// 		return ;
// 	if (!lst)
// 		*lst = new;
// 	else
// 	{
// 		new->next = *lst;
// 		*lst = new;
// 	}
// }

void ft_lstadd_front(t_list **list, t_list *new)
{
	if (!new)
		return ;
	if (!list)
		*list = new;
    new->next = (*list);
    if (!(*list))
        (*list)->prev = new;
    (*list) = new;
}
