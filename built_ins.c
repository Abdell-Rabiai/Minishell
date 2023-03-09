/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:31:12 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/09 16:40:56 by arabiai          ###   ########.fr       */
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
		if (!(*temp->variable_value))
			printf("declare -x %s\n", temp->variable_name);
		else
			printf("declare -x %s=\"%s\"\n", temp->variable_name, temp->variable_value);
		temp = temp->next;
	}
}

void export_variable(t_infos *infos, char *string)
{
	t_envp 	*temp;
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

int delete_head_envp(t_infos *infos, char *str)
{
	t_envp *temp;
	temp = infos->my_envp;
	if (!ft_strcmp(temp->next->variable_name, str))
	{
		printf("{ %s==%s }}\n", temp->next->variable_name, str);
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
			printf("{ %s==%s }}\n", temp->next->variable_name, str);
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
{
	t_envp *temp;
	t_envp *previous;
	temp = infos->my_envp;
	while (temp->next)
	{
		previous = temp;
		temp = temp->next;
	}
	if (!ft_strcmp(temp->variable_name, str))
	{
		printf("{ %s==%s }}\n", temp->variable_name, str);
		previous->next = NULL;
		free(temp);
		return (1);
	}
	else
		return (0);
}

int check_variable_regex_unset(char *str)
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

void unset(char *str, t_infos *infos)
{
	if (check_variable_regex_unset(str))
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
