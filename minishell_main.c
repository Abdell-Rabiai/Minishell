/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:24:53 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/11 12:19:48 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void loo(void)
{
	system("leaks minishell");
}

void ft_free_envp(t_infos *infos)
{
	(void)infos;
	t_envp *head;
	t_envp *temp2;

	head = infos->my_envp;
	while (head)
	{
		temp2 = head->next;
		free(head->variable_name);
		free(head->variable_value);
		free(head);
		head = temp2;
	}
}

void	ft_lstclear_envp(t_envp **lst)
{
	t_envp	*temp;

	if (!lst)
		return ;
	while (*lst && lst)
	{
		temp = (*lst)->next;
		free((*lst)->variable_name);
		free((*lst)->variable_value);
		free(*lst);
		(*lst) = temp;
	}
	lst = NULL;
}

int main(int ac, char **av, char **envp)
{
	// atexit(loo);
	(void)ac;
	(void)av;
	(void)envp;
	t_infos infos;
	init(&infos);
	duplicate_envp(envp, &infos);
	// // env(&infos);
	// printf("\n*--------------EXPORT-----------------*\n");
	// export(&infos);
	// export_variable(&infos, "Tabi3a");
	// export_variable(&infos, "Black");
	// export_variable(&infos, "BZaytona=");
	// export_variable(&infos, "B=""");
	// export_variable(&infos, "Tabi3a=dfaa3 sdaar haz rass o fuck l3alaam tkoon m9iwaad");
	// export_variable(&infos, "Tabi3a+= The_Greatest");
	// export_variable(&infos, "Black=1004");
	// export_variable(&infos, "Tabi3a+=Hello world from 1337");
	// export_variable(&infos, "Black=Security researcher");
	// export_variable(&infos, "*Black=");
	// // export_variable(&infos, "");
	// printf("\n*--------------EXPORT-----------------*\n");
	// // export(&infos);
	// unset("Tabi3a", &infos);
	// unset("Black", &infos);
	// unset("PATH", &infos);
	// unset("Apple_PubSub_Socket_Render", &infos);
	// unset("__CF_USER_TEXT_ENCODING", &infos);
	// unset("_P9K_TTY", &infos);
	// unset("", &infos);
	printf("\n*--------------AFTER UNSET PATH-----------------*\n");
	// export(&infos);
	printf("\n*--------------AFTER ENV-----------------*\n");
	// env(&infos);
	// echo("ps\n", 0);
	// pwd();
	// cd("*");
	// pwd();
	// ft_free_envp(&infos);
	ft_lstclear_envp(&infos.my_envp);
	while (1);
}