/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:16:02 by arabiai           #+#    #+#             */
/*   Updated: 2023/04/02 02:26:08 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_envp_value(char *variable_name, t_infos *infos)
{
	t_envp	*tmp;

	tmp = infos->my_envp;
	if (!variable_name)
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->variable_name, variable_name) == 0)
			return (tmp->variable_value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	get_envp_size(t_envp *envp)
{
	int		i;
	t_envp	*tmp;

	tmp = envp;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_free_envp_array(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char	**copy_envp_into_array(t_infos *infos)
{
	char	**envp;
	t_envp	*tmp;
	char	*string;
	int		i;
	int		envp_size;

	i = 0;
	tmp = infos->my_envp;
	envp_size = get_envp_size(infos->my_envp);
	envp = malloc(sizeof(char *) * (envp_size + 1));
	if (!envp)
		return (NULL);
	while (i < envp_size)
	{
		string = ft_strjoin(tmp->variable_name, "=", 0);
		envp[i] = ft_strjoin_env(string, tmp->variable_value, 1);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	update_shlvl_variable(t_infos *infos)
{
	t_envp	*temp;
	int		shlvl_old_value;
	char	*shlvl_new_value;

	temp = infos->my_envp;
	while (temp)
	{
		if (!ft_strcmp(temp->variable_name, "SHLVL"))
		{
			shlvl_old_value = ft_atoi(temp->variable_value);
			shlvl_old_value++;
			shlvl_new_value = ft_itoa(shlvl_old_value);
			free(temp->variable_value);
			temp->variable_value = shlvl_new_value;
			return ;
		}
		temp = temp->next;
	}
}
