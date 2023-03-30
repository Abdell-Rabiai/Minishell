/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:42:57 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/30 02:04:27 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	not_avalid_identifier(char *var_name, char *var_value)
{
	if (!var_value)
		ft_printf(2, "minishell: export: `%s': not a"
			"valid identifier\n", var_name);
	else
		ft_printf(2, "minishell: export: `%s%s': not a"
			"valid identifier\n", var_name, var_value);
	g_g.g_exit_status = 1;
	free(var_name);
}

void	add_the_variable(t_infos *infos, char *var_name, char *var_value)
{
	t_envp	*new_envp;

	if (var_name[ft_strlen(var_name) - 1] == '+')
		var_name[ft_strlen(var_name) - 1] = '\0';
	new_envp = new_node_envp(var_name, ft_strdup(var_value, 0));
	add_back_envp(&infos->my_envp, new_envp);
}
