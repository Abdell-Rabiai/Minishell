/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:22:16 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/16 15:06:51 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void my_export(char **strs, t_infos *infos)
{
	int i;
	
	i = 1;
	if (!strs[i])
		export(infos);
	while (strs[i])
	{
		export_variable(infos, strs[i]);
		i++;
	}
}

int check_variable_regex(char *str)
{
	int i;
	i = 0;

	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] == '+' && !str[i + 1])
			return (0) ;
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
		if (!ft_strcmp(temp->variable_name, "PATH") && get_envp_size(infos->my_envp) == 5)
			temp = temp->next;
		else if (!ft_strcmp(temp->variable_name, "_") && get_envp_size(infos->my_envp) == 5)
			temp = temp->next;
		else
		{
			if (!temp->variable_value)
				printf("declare -x %s\n", temp->variable_name);
			else if(!(*temp->variable_value))
				printf("declare -x %s=\"\"\n", temp->variable_name);
			else
				printf("declare -x %s=\"%s\"\n", temp->variable_name, temp->variable_value);
			temp = temp->next;	
		}
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
			if(!var_value)
				return (free(var_name)) ;
			else if (var_name[ft_strlen(var_name) - 1] == '+')
			{
				if (!temp->variable_value)
					temp->variable_value = ft_strdup("", 0);
				temp->variable_value = ft_strjoin(temp->variable_value, var_value, 1);
				return (free(var_name));
			}
			else
			{
				free(temp->variable_value);
				temp->variable_value = ft_strdup(var_value, 0);
				return (free(var_name));
			}
		}
		temp = temp->next;
	}
	if (var_name[ft_strlen(var_name) - 1] == '+')
		var_name[ft_strlen(var_name) - 1] = '\0';
	add_back_envp(&infos->my_envp, new_node_envp(var_name, ft_strdup(var_value, 0)));
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
		if (var_value == NULL)
			ft_printf(2, "minishell: export: `%s': not a valid identifier\n", var_name);
		else
			ft_printf(2, "minishell: export: `%s%s': not a valid identifier\n", var_name,var_value);
		free(var_name);
		return ;
	}
	if (var_value)
		var_value++;
    add_variable(infos, var_name, var_value);
}
