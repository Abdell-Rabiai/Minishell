/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:13:54 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/17 19:14:18 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_variable(char *str)
{
	int		i;
	char	*var;
	char	*var2;
	char	*value;

	i = 0;
	while (str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		i++;
	var = ft_substr(str, 1, i);
	var2 = ft_substr(str, ft_strlen(var) + 1, ft_strlen(str) - ft_strlen(var));
	value = getenv(var);
	if (!value)
		value = ft_strdup("", 0);
	value = ft_strjoin(value, var2, 0);
	free(var);
	free(var2);
	return (value);
}

bool	var_exist(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
				return (true);
		}
	}
	return (false);
}

void	expand_variables(t_list *tmp)
{
	char	*value;
	char	*tmp_str;
	int		i;

	i = 0;
	if (!is_expandable((tmp->content)))
		return ;
	while ((tmp->content)[i] != '$' && (tmp->content)[i])
		i++;
	if ((tmp->content)[i] == '$')
	{
		tmp_str = ft_substr((tmp->content), 0, i);
		value = get_variable((tmp->content) + i);
		i--;
		free(tmp->content);
		tmp->content = ft_strjoin(tmp_str, value, 1);
		free(value);
	}
}

void	expand_multi_vars(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->prev && tmp->prev->type == here_doc)
			tmp = tmp->next;
		if (tmp)
		{
			while (var_exist(tmp->content) && is_expandable(tmp->content))
				expand_variables(tmp);
			tmp = tmp->next;
		}
	}
}

bool	is_expandable(char *str)
{
	int			i;
	static bool	s_quote_open;
	static bool	d_quote_open;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && !d_quote_open)
			s_quote_open = !s_quote_open;
		else if (str[i] == '\"')
			d_quote_open = !d_quote_open;
		if (str[i] == '$' && !s_quote_open)
			return (true);
	}
	return (false);
}
