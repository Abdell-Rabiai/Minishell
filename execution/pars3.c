/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:09:49 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/13 16:44:11 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
}

void	add_or_join(t_list **head, char *temp, t_list **temp2)
{
	if ((*temp2) && what_type(temp) == word && what_type((*temp2)->content) == word)
	{
		(*temp2)->content = ft_strjoin((*temp2)->content, " ", 0);
		(*temp2)->content = ft_strjoin((*temp2)->content, temp, 0);
	}
	else
	{
		(*temp2) = ft_lstnew(ft_strtrim(temp, " "));
		(*temp2)->type = what_type(temp);
		ft_lstadd_back(head, (*temp2));
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
	if (temp->type == trunc && temp->next && temp->next->type != word
		&& temp->next->type != Pipe)
		return (print_error(*str), 1);
	return (0);
}

int	check_pars_errors(t_list *command)
{
	t_list	*temp;
	char	*str;

	temp = command;
	str = "\\n";
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
		if (temp->type == in_redir && temp->next && temp->next->type != word
			&& temp->next->type != in_file)
			return (print_error(*str), 1);
		if (temp->type == append && temp->next && temp->next->type != word
			&& temp->next->type != out_file)
			return (print_error(*str), 1);
		if (check_pars_erros2(temp, str))
			return (print_error(*str), 1);
		if (check_pars_syntax(temp->content))
			return (1);
		temp = temp->next;
	}
	return (0);
}

int check_pars_syntax(char *str)
{
	t_type	type;
	int		i;

	i = 0;
	type = what_type(str);
	while (str[i])
	{
		if (type == 2 || type == 6)
			i += 2;
		else if (!type)
			return (0);
		else
			i += 1;
		if (str[i] && what_type(str + i) == type)
			return (print_error(str[i]), 1);
	}
	return (0);
}