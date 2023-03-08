/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:34:10 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/08 19:09:28 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
            if (ft_strncmp(tmp_envp->variable_name, tmp->variable_name, ft_strlen(tmp_envp->variable_name)) > 0)
                swap_envp_nodes(tmp_envp, tmp);
            tmp = tmp->next;
        }
       tmp_envp = tmp_envp->next;
    }
}

t_envp	*new_node_envp(char *v_name, char *v_value)
{
	t_envp	*new_node;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
	(*new_node).variable_name = v_name;
    (*new_node).variable_value = v_value;
	(*new_node).next = NULL;
	return (new_node);
}

void	add_back_envp(t_envp **lst, t_envp *new)
{
	t_envp	*temp;

	if (!new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void duplicate_envp(char **envp, t_infos *infos)
{
	int i;
    char *v_name;
    char *v_value;

	i = 0;
	while (envp[i] != NULL)
	{
        v_name = get_variable_name(envp[i]);
        v_value = get_variable_value(envp[i]);
        add_back_envp(&infos->my_envp, new_node_envp(v_name, v_value));
		i++;
	}
}

char *get_variable_value(char *string)
{
	int i;
	char *variable_value;

	i = 0;
	while (string[i] != '=')
		i++;
	variable_value = ft_substr(string, i + 1, ft_strlen(string) - i);
	return (variable_value);
}

char *get_variable_name(char *string)
{
	int i;
	char *variable_name;

	i = 0;
	while (string[i] != '=')
		i++;
	variable_name = ft_substr(string, 0, i);
	return (variable_name);
}
