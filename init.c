/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:35:55 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/06 21:36:11 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init(t_infos *infos)
{ 
	infos = (t_infos *)malloc(sizeof(t_infos));
	infos->my_envp = (t_envp *)malloc(sizeof(t_envp));
}

