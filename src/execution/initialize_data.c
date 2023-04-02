/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:35:55 by arabiai           #+#    #+#             */
/*   Updated: 2023/04/02 18:43:28 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prompt_helper(char *str, t_list *final_list, t_infos *infos)
{
	infos->pids = malloc(sizeof(pid_t) * ft_lstsize(final_list));
	if (!infos->pids)
		return (free_final_list(final_list), free(str));
	execute(final_list, infos);
	free_final_list(final_list);
	free(str);
}

void	initt(t_infos *infos)
{
	(void)infos;
	infos->my_envp = NULL;
}
