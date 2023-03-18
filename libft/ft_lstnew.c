/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:35:31 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/18 17:23:48 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list    *ft_lstnew(void *content)
{
    t_list    *elem;

    elem = malloc(sizeof(t_list));
    if (!elem)
        return (NULL);
    elem->content = content;
    elem->prev = NULL;
    elem->next = NULL;
    elem->out_file = NULL;
    elem->in_file = NULL;
    elem->in_fd = -2;
    elem->out_fd = -2;
    elem->_errno = 0;
    elem->delims = NULL;
    elem->commands = NULL;
    return (elem);
}
