/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:18:23 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/15 18:37:40 by arabiai          ###   ########.fr       */
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
void	my_export(char **strs, t_infos *infos);
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
void	my_unset(char **strs, t_infos *infos);
void	unset_variable(char *str, t_infos *infos);
int		delete_head_envp(t_infos *infos, char *str);
int		delete_node_envp(t_infos *infos, char *str);
int		delete_tail_envp(t_infos *infos, char *str);

/*---------> env <--------*/
void	my_env(t_infos *infos);
char 	*get_envp_value(char *variable_name, t_infos *infos);
void 	set_envp_value(char *old_variable, char *current_variable, t_infos *infos);
void	update_shlvl_variable(t_infos *infos);

/*--------->builtins util funtions <--------*/
int		check_for_newline_option(char *str);
void	my_echo(char **strs);
void    my_pwd(void);
void	my_cd(char **strs, t_infos *infos);
void    cd(char *path);
void	my_exit(char **strs, t_infos *infos);

/*---------> execution <--------*/
void	execute_one_cmd(char **strs, char **envp);
char	**copy_envp_into_array(t_infos *infos);
void	print_envp_array(char **envp, t_infos *infos);
int		get_envp_size(t_envp *envp);
void	ft_free_envp_array(char **envp);

/**AHMAYMOU*/

typedef enum TYPE
{
	word,/*0*/
	trunc,/*1*/
	here_doc,/*2*/
	in_redir,/*3*/
	delimiter,/*4*/
	in_file,/*5*/
	append,/*6*/
	out_file,/*7*/
	Pipe /*8*/
}			t_type;

void	prompt(t_infos *infos);
void	echo(char *str, bool option);
void	pwd(void);
void	change_dir(char *path);
void	handle_kill(int sig);
bool	count_quotes(char *str);
int		end_word_index(char *str);
bool	is_spec(char str);
int		end_word_index(char *str);
void	add_or_join(t_list **head, char *temp, t_list **temp2);
void	assign_type(t_list *command);
t_type	what_type(char *cmd);
int		check_pars_errors(t_list *command);
int		check_pars_syntax(char *str);
int		check_pars_erros2(t_list *temp, char *str);

#endif