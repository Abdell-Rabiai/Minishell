/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:24:53 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/08 19:19:48 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void loo(void)
{
	system("leaks minishell");
}

int main(int ac, char **av, char **envp)
{
	atexit(loo);
	(void)ac;
	(void)av;
	(void)envp;
	t_infos infos;
	init(&infos);
	duplicate_envp(envp, &infos);
	// env(&infos);
	printf("\n*--------------EXPORT-----------------*\n");
	export(&infos);
	export_variable(&infos, "Tabi3a");
	export_variable(&infos, "Tabi3a=3alam Khoore");
	export_variable(&infos, "Black=1004");
	export_variable(&infos, "Tabi3a=Hello world from 1337");
	export_variable(&infos, "Black=Security researcher");
	export_variable(&infos, "Black");
	printf("\n*--------------EXPORT-----------------*\n");
	export(&infos);
	// unset("PATH", envp);
	// printf("\n*--------------AFTER UNSET PATH-----------------*\n");
	// export(envp);
	// printf("\n*--------------AFTER ENV-----------------*\n");
	// env(&infos);
	// 
	while (1);
}