/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:18:23 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/11 16:38:18 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <ctype.h>
# include <readline/history.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct s_envp
{
	char			*variable_name;
	char 			*variable_value;
	struct s_envp	*next;
} t_envp;

typedef struct s_infos
{
	struct s_envp	*my_envp;
} t_infos;


/*---------> initialize_data <--------*/
void init(t_infos *infos);

/*---------> basic builtins funtions <--------*/
void    echo(char *str, bool option);
void    pwd(void);
void    cd(char *path);

/*---------> export <--------*/
void    export(t_infos *infos);
void	swap_envp_nodes(t_envp *tmp_envp, t_envp *tmp);
void	sort_envp(t_infos *infos);
void	export_variable(t_infos *infos, char *string);
void	add_variable(t_infos *infos, char *var_name, char *var_value);
int		check_variable_regex(char *str);
char 	*get_variable_value(char *string);
char	*get_variable_name(char *string);
t_envp	*new_node_envp(char *v_name, char *v_value);
void	add_back_envp(t_envp **head, t_envp *new);
void 	duplicate_envp(char **envp, t_infos *infos);
void	ft_free_envp(t_envp **head);

/*---------> unset <--------*/
void	unset(char *str, t_infos *infos);
int		delete_head_envp(t_infos *infos, char *str);
int		delete_node_envp(t_infos *infos, char *str);
int		delete_tail_envp(t_infos *infos, char *str);

/*---------> env <--------*/
void env(t_infos *infos);

/*--------->builtins util funtions <--------*/
void    echo(char *str, bool option);
void    pwd(void);
void    cd(char *path);
void    exitt(void);
#endif