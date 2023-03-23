/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:54:39 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/21 17:42:31 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_tokens(const char *str)
{
	int			count;
	int			in_quotes;
	const char	*p;

	in_quotes = 0;
	p = str;
	count = 0;
	while (*p != '\0')
	{
		if (*p == '\"' || *p == '\'')
		{
			if (in_quotes == 0)
				in_quotes = *p;
			else if (in_quotes == *p)
				in_quotes = 0;
		}
		else if ((*p == ' ' || *p == '\t') && !in_quotes)
			count++;
		p++;
	}
	return (count + 1);
}

char	*extract_token(const char *start, const char *str)
{
	char	*token;
	int		len;

	len = str - start;
	token = malloc((len + 1) * sizeof(char));
	ft_strncpy(token, start, len);
	token[len] = '\0';
	return (token);
}

int	init_split_string(const char *str, int *nt, int *in_q, char **t)
{
	*nt = 0;
	*in_q = 0;
	t = malloc(count_tokens(str) * sizeof(char *));
	if (!t)
		return (0);
	return (1);
}

char	**split_string(const char *str, int in_quotes, int num_tokens)
{
	const char	*start;
	char		**tokens;

	tokens = malloc(count_tokens(str) * sizeof(char *));
	if (!tokens)
		return (NULL);
	start = str;
	while (*str != '\0')
	{
		if (*str == '\'' || *str == '\"')
		{
			if (in_quotes == 0)
				in_quotes = *str;
			else if (in_quotes == *str)
				in_quotes = 0;
		}
		else if ((*str == ' ' || *str == '\t') && !in_quotes)
		{
			tokens[num_tokens++] = extract_token(start, str);
			start = str + 1;
		}
		str++;
	}
	return (tokens[num_tokens] = NULL, tokens);
}
