/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:31:12 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/07 17:30:18 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    echo(char *str, bool option)
{
	if (option)
		printf("%s", str);
	else
		printf("%s\n", str);
}

void    pwd(void)
{
	char    str[256];

	if (!getcwd(str, sizeof(str)))
		printf("Error printing current working directory!\n");
	else
		printf("%s\n", str);
}

void    cd(char *path)
{
	if (chdir(path))
		printf("Error changing directory!\n");
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
		if (ft_strncmp(temp->variable_value, "", ft_strlen(temp->variable_value)) == 0)
			printf("declare -x %s\n", temp->variable_name);
		else
			printf("declare -x %s=\"%s\"\n", temp->variable_name, temp->variable_value);
		temp = temp->next;
	}
}

void export_variable(t_infos *infos, char *string)
{
	t_envp 	*temp;
	t_envp 	*new_node;
	char	*var_value;
	char 	*var_name;

	temp = infos->my_envp;
	var_name = ft_substr(string, 0, ft_strchr(string, '=') - string);
	var_value = ft_strchr(string, '=');
	if (!var_value)
		var_value = "";
	else
		var_value++;
	while (temp)
	{
		if (ft_strncmp(temp->variable_name, var_name, ft_strlen(temp->variable_name)) == 0)
			return ;
		temp = temp->next;
	}
	new_node = new_node_envp(var_name, var_value);
	add_back_envp(&infos->my_envp, new_node);
}

void unset(char *str, char **envp)
{
	(void)str;
	int i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			free(envp[i]);
		i++;
	}
}

void env(t_infos *infos)
{
	t_envp *temp;
	temp = infos->my_envp;
	while (temp)
	{
		printf("%s=%s\n", temp->variable_name, temp->variable_value);
		temp = temp->next;
	}
}
