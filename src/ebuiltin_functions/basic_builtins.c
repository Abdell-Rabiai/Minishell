/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:34:06 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/31 01:46:37 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_pwd(t_infos *infos)
{
	char	str[256];

	if (!getcwd(str, sizeof(str)))
	{
		if (get_envp_value("PWD", infos))
			ft_printf(1, "%s\n", get_envp_value("PWD", infos));
		else
			ft_printf(1, "Oops! i'm lost, the location where you are doesn't"
				" appear to exist, try go somewhere else\n");
	}
	else
		ft_printf(1, "%s\n", str);
}

void	my_exit(char **strs, pid_t pid, t_infos *infos)
{
	static int	i;

	if (pid != 0)
		ft_printf(1, "exit\n");
	if (strs[1])
	{
		g_g.g_exit_status = (unsigned char)ft_atoi_exit(strs[1], &i);
		if (i == 1)
		{
			ft_printf(2, "my_minishell: exit: %s: numeric argument required\n",
				strs[1]);
			g_g.g_exit_status = 255;
		}
		else if (!i && (strs[1] && strs[2]))
		{
			ft_printf(2, "my_minishell: exit: too many arguments\n");
			g_g.g_exit_status = EXIT_FAILURE;
			return ;
		}
	}
	else
		g_g.g_exit_status = EXIT_SUCCESS;
	clear_history();
	ft_free_envp_array(infos->envp);
	exit(g_g.g_exit_status);
}
