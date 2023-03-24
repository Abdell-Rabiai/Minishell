/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:09:17 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/24 23:09:54 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
