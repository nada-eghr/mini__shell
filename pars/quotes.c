/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:19:23 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/01 13:37:25 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_single_quote(char **str, int *s_quote)
{
	if (**str == '\'')
	{
		*s_quote = 1;
		(*str)++;
		while (**str && **str != '\'')
			(*str)++;
		if (**str == '\'')
		{
			*s_quote = 0;
			(*str)++;
		}
	}
}

static void	check_double_quote(char **str, int *d_quote)
{
	if (**str == '"')
	{
		*d_quote = 1;
		(*str)++;
		while (**str && **str != '"')
			(*str)++;
		if (**str == '"')
		{
			*d_quote = 0;
			(*str)++;
		}
	}
}

int	check_quotes(char *str, t_var *var)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (*str)
	{
		if (*str == '\'')
			check_single_quote(&str, &s_quote);
		else if (*str == '"')
			check_double_quote(&str, &d_quote);
		else
			str++;
	}
	if (s_quote || d_quote)
	{
		printf("minishell: unclosed quotes\n");
		var->exit_stat = 258;
		return (1);
	}
	return (0);
}
