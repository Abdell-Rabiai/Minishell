/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:34:10 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/06 21:54:04 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sort_envp(char **envp)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    while (envp[i])
    {
        j = i + 1;
        while (envp[j])
        {
            if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
            {
                tmp = envp[i];
                envp[i] = envp[j];
                envp[j] = tmp;
            }
            j++;
        }
        i++;
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


void print_envp(t_infos *infos)
{
	t_envp *tmp_env;

	tmp_env = infos->my_envp;
	while (tmp_env != NULL)
	{
		printf("%s=", tmp_env->variable_name);
		printf("%s\n", tmp_env->variable_value);
		tmp_env = tmp_env->next;
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
