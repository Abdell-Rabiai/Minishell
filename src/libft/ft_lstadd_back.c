/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackhole <blackhole@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:53:38 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/06 12:38:14 by blackhole        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*temp;

// 	temp = *lst;
// 	if (!new)
// 		return ;
// 	if ((*lst))
// 	{
// 		while (temp->next)
// 			temp = temp->next;
// 		temp->next = new;
// 	}
// 	else
// 		*lst = new;
// }
    // t_list *new_node = (Node*)malloc(sizeof(Node));
    // new_node->data = data;
    // new_node->prev = NULL;
    // new_node->next = NULL;
void ft_lstadd_back(t_list **list,t_list *new)
{
	if (!new)
		return ;
    if (!(*list))
        *list = new;
    else
	{
        t_list *current = (*list);
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
        new->prev = current;
    }
}

