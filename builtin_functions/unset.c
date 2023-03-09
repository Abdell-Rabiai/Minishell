/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:31:12 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/09 19:01:21 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void unset(char *str, t_infos *infos)
{
	if (check_variable_regex(str))
	{
		ft_printf(2, "minishell: unset: `%s': not a valid identifier\n", str);
		return ;
	}
	if (delete_head_envp(infos, str))
		return ;
	else
	{
		if (delete_node_envp(infos, str))
			return ;
		else
			delete_tail_envp(infos, str);
	}
}

int delete_head_envp(t_infos *infos, char *str)
{
	t_envp *temp;
	temp = infos->my_envp;
	if (!ft_strcmp(temp->next->variable_name, str))
	{
		infos->my_envp = infos->my_envp->next;
		free(temp);
		return (1);
	}
	else
		return (0);
}

int delete_node_envp(t_infos *infos, char *str)
{
	t_envp *temp;
	t_envp *curr;
	temp = infos->my_envp;
	while (temp->next)
	{
		if (!ft_strcmp(temp->next->variable_name, str))
		{
			curr = temp->next;
			temp->next = temp->next->next; 
			free(curr);
			return (1);
		}
		else
			temp = temp->next;
	}
	return (0);
}

int delete_tail_envp(t_infos *infos, char *str)
{	t_envp *temp;
	t_envp *previous;
	temp = infos->my_envp;
	while (temp->next)
	{
		previous = temp;
		temp = temp->next;
	}
	if (!ft_strcmp(temp->variable_name, str))
	{
		previous->next = NULL;
		free(temp);
		return (1);
	}
	else
		return (0);
}