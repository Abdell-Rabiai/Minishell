/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:34:10 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/30 01:55:24 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	add_back_envp(t_envp **head, t_envp *new)
{
	t_envp	*temp;

	temp = *head;
	if (!new)
		return ;
	if ((*head))
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		*head = new;
}

char	*get_variable_value(char *string)
{
	int		i;
	char	*variable_value;

	i = 0;
	while (string[i] != '=')
		i++;
	variable_value = ft_substr(string, i + 1, ft_strlen(string) - i);
	return (variable_value);
}

char	*get_variable_name(char *string)
{
	int		i;
	char	*variable_name;

	i = 0;
	while (string[i] != '=')
		i++;
	variable_name = ft_substr(string, 0, i);
	return (variable_name);
}

void	duplicate_envp(char **envp, t_infos *infos)
{
	int		i;
	char	*v_name;
	char	*v_value;

	i = 0;
	while (envp[i] != NULL)
	{
		v_name = get_variable_name(envp[i]);
		v_value = get_variable_value(envp[i]);
		add_back_envp(&infos->my_envp, new_node_envp(v_name, v_value));
		i++;
	}
	if (envp[0] == NULL)
	{
		add_ignored_env(infos);
		infos->ignore = true;
	}
	else
		infos->ignore = false;
	set_envp_value("OLDPWD", "", infos);
}
