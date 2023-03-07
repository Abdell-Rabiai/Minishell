/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:24:53 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/07 19:43:35 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_infos infos;
	init(&infos);
	duplicate_envp(envp, &infos);
	// env(&infos);
	printf("\n*--------------EXPORT-----------------*\n");
	export(&infos);
	export_variable(&infos, "Tabi3a");
	export_variable(&infos, "TabBlack="1004");
	export_variable(&infos, "Tabi3a=Hello world from 1337");
	export_variable(&infos, "Tabi3a=3ALAM KHOOR");
	export_variable(&infos, "TabBlack="Security researcher");
	export(&infos);
	// unset("PATH", envp);
	// printf("\n*--------------AFTER UNSET PATH-----------------*\n");
	// export(envp);
	printf("\n*--------------AFTER ENV-----------------*\n");
	env(envp);
}