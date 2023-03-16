/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:30:43 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/16 15:10:09 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_ignored_env(t_infos *infos)
{
	add_back_envp(&infos->my_envp, new_node_envp("PWD", ft_strdup(getcwd(NULL, 0), 1)));
	add_back_envp(&infos->my_envp, new_node_envp("SHLVL", ft_strdup("1", 0)));
	add_back_envp(&infos->my_envp, new_node_envp("_", ft_strjoin(ft_strdup(getcwd(NULL, 0), 1), "./minishell", 1)));
	add_back_envp(&infos->my_envp, new_node_envp("OLDPWD", ft_strdup("", 0)));
	add_back_envp(&infos->my_envp, new_node_envp("PATH", ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin", 0)));
}

char *get_envp_value(char *variable_name, t_infos *infos)
{
	t_envp *tmp;

	tmp = infos->my_envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->variable_name, variable_name) == 0)
				return (tmp->variable_value);
		tmp = tmp->next;
	}
	return (NULL);
}

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

void my_env(t_infos *infos)
{
	t_envp *temp;

	temp = infos->my_envp;
	while (temp != NULL)
	{
		if (temp->variable_value)
		{
			if (!ft_strcmp(temp->variable_name, "PATH") && get_envp_size(infos->my_envp) == 5)
				temp = temp->next;
			else if (!ft_strcmp(temp->variable_name, "OLDPWD") && get_envp_size(infos->my_envp) == 5)
				temp = temp->next;
			else
			{
				printf("%s=%s\n", temp->variable_name, temp->variable_value);
				temp = temp->next;
			}
		}
	}
}
