/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:30:43 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/11 16:38:08 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void swap_envp_nodes(t_envp *tmp_envp, t_envp *tmp)
{
	char *tmp_value;
	char *tmp_name;

	tmp_name = tmp_envp->variable_name;
	tmp_value = tmp_envp->variable_value;
	tmp_envp->variable_name = tmp->variable_name;
	tmp_envp->variable_value = tmp->variable_value;
	tmp->variable_name = tmp_name;
	tmp->variable_value = tmp_value;
}

void	ft_free_envp(t_envp **head)
{
	t_envp	*temp;

	if (!head)
		return ;
	while (*head)
	{
		temp = (*head)->next;
		free((*head)->variable_name);
		free((*head)->variable_value);
		free(*head);
		(*head) = temp;
	}
	head = NULL;
}

void sort_envp(t_infos *infos)
{
    t_envp *tmp_envp;
	t_envp *tmp;

	tmp_envp = infos->my_envp;
    while (tmp_envp)
    {
        tmp = tmp_envp->next;
        while (tmp)
        {
            if (ft_strcmp(tmp_envp->variable_name, tmp->variable_name) > 0)
                swap_envp_nodes(tmp_envp, tmp);
            tmp = tmp->next;
        }
       tmp_envp = tmp_envp->next;
    }
}

void env(t_infos *infos)
{
	t_envp *temp;

	temp = infos->my_envp;
	while (temp != NULL)
	{
		if (temp->variable_value)
			printf("%s=%s\n", temp->variable_name, temp->variable_value);
		temp = temp->next;
	}
}
