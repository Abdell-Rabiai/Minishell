/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:22:16 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/09 18:32:00 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_variable_regex(char *str)
{
	int i;
	i = 0;

	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void export(t_infos *infos)
{
	int i;
	t_envp *temp;

	i = 0;
	sort_envp(infos);
	temp = infos->my_envp;
	while (temp)
	{
		if (!(*temp->variable_value))
			printf("declare -x %s\n", temp->variable_name);
		else
			printf("declare -x %s=\"%s\"\n", temp->variable_name, temp->variable_value);
		temp = temp->next;
	}
}

void add_variable(t_infos *infos, char *var_name, char *var_value)
{
    t_envp 	*temp;

	temp = infos->my_envp;
    while (temp)
	{
		if (!ft_strncmp(temp->variable_name, var_name, ft_strlen(temp->variable_name)))
		{
			if(!ft_strncmp(var_value, "", ft_strlen(var_value)))
			{
				free(var_name);
				return ;
			}
			else
			{
				temp->variable_value = var_value;
				free(var_name);
				return ;
			}
		}
		temp = temp->next;
	}
	add_back_envp(&infos->my_envp, new_node_envp(var_name, var_value));
}

void export_variable(t_infos *infos, char *string)
{
	t_envp 	*temp;
	char	*var_value;
	char 	*var_name;

	temp = infos->my_envp;
	var_name = ft_substr(string, 0, ft_strchr(string, '=') - string);
	var_value = ft_strchr(string, '=');
	if (check_variable_regex(var_name))
	{
		ft_printf(2, "minishell: export: `%s': not a valid identifier\n", var_name);
		return ;
	}
	if (!var_value)
		var_value = "";
	else
		var_value++;
    add_variable(infos, var_name, var_value);
}
