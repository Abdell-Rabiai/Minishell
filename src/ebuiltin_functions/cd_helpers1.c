/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 21:48:54 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/24 18:06:02 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_envp_value(char *old_variable, char *new_value, t_infos *infos)
{
	t_envp	*temp;

	temp = infos->my_envp;
	while (temp)
	{
		if (!ft_strcmp(temp->variable_name, old_variable))
		{
			free(temp->variable_value);
			temp->variable_value = ft_strdup(new_value, 0);
			return ;
		}
		temp = temp->next;
	}
}

int	print_old_pwd(t_infos *infos)
{
	char	*old_pwd;

	old_pwd = get_envp_value("OLDPWD", infos);
	if (!old_pwd)
	{
		ft_printf(2, "minishell: cd: OLDPWD not set\n");
		return (1);
	}
	if (!ft_strcmp(old_pwd, ""))
	{
		ft_printf(2, "minishell: cd: OLDPWD not set\n");
		return (1);
	}
	ft_printf(1, "%s\n", old_pwd);
	cd(old_pwd, infos);
	return (0);
}
