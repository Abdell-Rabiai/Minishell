/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:42:34 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/24 23:00:54 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **list, t_list *new)
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
