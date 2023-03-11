/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:24:53 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/11 16:07:03 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void loo(void)
{
	system("leaks minishell");
}

// void ft_free_envp(t_infos *infos)
// {
// 	(void)infos;
// 	t_envp *head;
// 	t_envp *temp2;

// 	head = infos->my_envp;
// 	while (head)
// 	{
// 		temp2 = head->next;
// 		free(head->variable_name);
// 		free(head->variable_value);
// 		free(head);
// 		head = temp2;
// 	}
// }

void	ft_lstclear_envp(t_envp *lst)
{
	t_envp	*temp;

	if (!lst)
		return ;
	while (lst )
	{
		temp = (lst)->next;
		free((lst)->variable_name);
		free((lst)->variable_value);
		free(lst);
		(lst) = temp;
	}
	lst = NULL;
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
	export(&infos);
	env(&infos);
	export_variable(&infos, "Tabi3a");
	export_variable(&infos, "Tabi3a=1");
	export_variable(&infos, "Tabi3a=2");
	export_variable(&infos, "Tabi3a=3");
	export_variable(&infos, "Tabi3a=4");
	export_variable(&infos, "Tabi3a=5");
	export_variable(&infos, "Tabi3a=dfaa3 sdaar haz rass o fuck l3alaam tkoon m9iwaad");
	export_variable(&infos, "Tabi3a=opps");
	export_variable(&infos, "Tab");
	export_variable(&infos, "Tab=12");
	export_variable(&infos, "Black=1004");
	export_variable(&infos, "Black+=/Security researcher");
	export_variable(&infos, "*Black=");
	export_variable(&infos, "");
	printf("\n*--------------AFTER UNSET PATH-----------------*\n");
	unset("Tabi3a", &infos);
	unset("COLORTERM", &infos);
	unset("BZaytona", &infos);
	unset("Black", &infos);
	unset("PATH", &infos);
	unset("Apple_PubSub_Socket_Render", &infos);
	unset("__CF_USER_TEXT_ENCODING", &infos);
	unset("_P9K_TTY", &infos);
	unset("ZSH", &infos);
	printf("\n*--------------EXPORT-----------------*\n");
	printf("\n*--------------ENV-----------------*\n");
	export(&infos);
	printf("\n*--------------AFTER ENV-----------------*\n");
	env(&infos);
	echo("ps\n", 0);
	pwd();
	cd("*");
	pwd();
	ft_lstclear_envp(infos.my_envp);
	// ft_free_envp(&infos);
	// while (1);
}
