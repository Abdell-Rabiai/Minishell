/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:19:04 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/18 21:42:02 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_kill(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_clear_history();
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}

bool	count_quotes(char *str)
{
	bool	d_is_opened;
	bool	s_is_opened;

	d_is_opened = 0;
	s_is_opened = 0;
	while (*str)
	{
		if (*str == 34)
			d_is_opened = !d_is_opened;
		else if (*str == 39 && !d_is_opened)
			s_is_opened = !s_is_opened;
		str++;
	}
	if (!d_is_opened && !s_is_opened)
		return (1);
	else
		return (0);
}

bool	is_spec(char str)
{
	if (str == '<' || str == '>' || str == '|' || str == ' ')
		return (true);
	else
		return (false);
}

int	get_cmd_quotes(char *str)
{
	char	c;
	int		i;

	i = -1;
	if (str[++i] == 34 || str[i] == 39)
	{
		c = str[i];
		while (str[++i] && str[i] != c)
			;
		return (i + 1);
	}
	return (-1);
}

int	end_word_index(char *str)
{
	int		i = -1;
	char	c;
	bool	quote_open;

	// i = get_cmd_quotes(str);
	quote_open = false;
	// if (i != -1)
	// 	return (i);
	while (str[++i])
	{
		if (str[i] == 39 || str[i] == 34)
			quote_open = !quote_open;
		if (is_spec(str[i]) && i && !quote_open)
			return (i);
		else if (is_spec(str[i]) && !quote_open)
		{
			c = str[i];
			while (str[i++] == c)
				;
			if (i == 1)
				return (1);
			return (i - 1);
		}
	}
	return (-1);
}

