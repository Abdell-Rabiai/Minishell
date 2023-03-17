/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:54:39 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/17 19:43:57 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int count_tokens(const char* str)
{
	int count;
	int in_quotes;
	const char* p;

	in_quotes = 0;
	p = str;
	count = 0;
	while (*p != '\0')
	{
		if (*p == '\"')
			in_quotes = !in_quotes;
		else if (*p == ' ' && !in_quotes)
			count++;
		p++;
	}
	return (count + 1);
}

char*	extract_token(const char* start, const char *str)
{
	char* 	token;
	int		len;

	len = str - start;
	token = malloc((len + 1) * sizeof(char));
	ft_strncpy(token, start, len);
	token[len] = '\0';
	return token;
}

char**	split_string(const char* str)
{
	int			num_tokens;
	bool		in_quotes;
	const char*	start;
	char**		tokens;

	in_quotes = 0;
	num_tokens = 0;
	tokens = malloc(count_tokens(str) * sizeof(char*));
	start = &str[0];
	while (*str != '\0')
	{
		if (*str == '\'' || *str == '\"')
			in_quotes = !in_quotes;
		else if (*str == ' ' && !in_quotes)
		{
			tokens[num_tokens] = extract_token(start, str);
			start = str + 1;
			num_tokens++;
		}
		str++;							
	}
	// tokens[num_tokens] = extract_token(start, str);
	return (tokens[num_tokens] = NULL, tokens);
}
