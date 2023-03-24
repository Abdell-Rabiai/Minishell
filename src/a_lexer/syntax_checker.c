/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:09:49 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/22 18:59:22 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char c)
{
	g_exit_status = 258;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (c == '\n')
		ft_putstr_fd("newline", 2);
	else
		ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
}

void	add_or_join(t_list **head, char *temp, t_list **temp2, int *red_c)
{
	if ((*temp2) && what_type(temp) == word
		&& (*temp2)->type == word && *red_c % 2)
	{
		(*temp2)->content = ft_strjoin((*temp2)->content, " ", 1);
		(*temp2)->content = ft_strjoin((*temp2)->content, temp, 1);
	}
	else
	{
		(*temp2) = ft_lstnew(ft_strtrim(temp, " "));
		(*temp2)->type = what_type(temp);
		ft_lstadd_back(head, (*temp2));
		*red_c = 0;
	}
}

int	check_pars_erros2(t_list *temp, char *str)
{
	if (temp->type == here_doc && !temp->next)
		return (print_error(*str), 1);
	if (temp->type == here_doc && temp->next && temp->next->type != word
		&& temp->next->type != delimiter)
		return (print_error(*str), 1);
	if (temp->type == trunc && !temp->next)
		return (print_error(*str), 1);
	if (temp->type == trunc && temp->next && (temp->next->type != tr_out_file
			&& temp->next->type != app_out_file))
		return (print_error(*str), 1);
	return (0);
}

int	check_pars_errors3(t_list *temp, char *str)
{
	if (temp->type == in_redir && temp->next && temp->next->type != word
		&& temp->next->type != in_file && temp->next->type != trunc)
		return (print_error(*str), 1);
	if (temp->type == append && temp->next && temp->next->type != word
		&& temp->next->type != tr_out_file && temp->next->type != app_out_file)
		return (print_error(*str), 1);
	if (check_pars_erros2(temp, str))
		return (1);
	if (check_pars_syntax(temp->content))
		return (1);
	return (0);
}

int	check_pars_errors(t_list *command)
{
	t_list	*temp;
	char	*str;

	temp = command;
	str = "'newline'";
	while (temp)
	{
		if (temp->next)
			str = temp->next->content + ft_strlen(temp->next->content) - 1;
		if (temp->type == Pipe && !temp->next)
			return (print_error(*str), 1);
		if (temp->type == Pipe && temp->next && temp->next->type == Pipe)
			return (print_error(*str), 1);
		if (temp->type == in_redir && !temp->next)
			return (print_error(*str), 1);
		if (check_pars_errors3(temp, str))
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	check_pars_syntax(char *str)
{
	t_type	type;
	int		i;

	i = 0;
	type = what_type(str);
	while (str[i])
	{
		if (ft_strlen(str + i) > 1 && !ft_strncmp(str + i, "&&", 2))
			return (print_error(str[i]), 1);
		if (type == 2 || type == 6)
			i += 2;
		else if (!type)
			return (0);
		else
			i += 1;
		if ((str[i] && what_type(str + i) == type)
			|| (str[i] && what_type(str + i) == 1 && type == 6)
			|| (str[i] && what_type(str + i) == 3 && type == 2))
			return (print_error(str[i]), 1);
	}
	return (0);
}
