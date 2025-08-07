/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:05:43 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/03 17:52:56 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*parse_operator_token(const char *data, int *i)
{
	int		j;
	char	tmp[3];

	j = 0;
	if (((data[*i] == '>' && data[*i + 1] == '>') || (data[*i] == '<'
				&& data[*i + 1] == '<')) && data[*i] != '|')
		tmp[j++] = data[(*i)++];
	tmp[j++] = data[(*i)++];
	tmp[j] = '\0';
	return (creattoken(tmp));
}

t_token	*parse_quoted_token(const char *data, int *i)
{
	char	quote;
	int		start;
	int		end;
	char	*new;
	t_token	*token;

	quote = data[*i];
	start = (*i)++;
	while (data[*i] && data[*i] != quote)
		(*i)++;
	(*i)++;
	end = *i;
	new = substr(data, start, end - start);
	token = creattoken(new);
	free(new);
	return (token);
}

t_token	*parse_word_token(const char *data, int *i)
{
	int		start;
	int		end;
	char	*new;
	t_token	*token;

	start = *i;
	while (data[*i] && !ft_space(data[*i]) && data[*i] != '>' && data[*i] != '<'
		&& data[*i] != '|' && data[*i] != '\"' && data[*i] != '\'')
		(*i)++;
	end = *i;
	new = substr(data, start, end - start);
	token = creattoken(new);
	free(new);
	return (token);
}

t_token	*handle_spaces(const char *data, int *i)
{
	t_token	*token;

	token = creattoken(" ");
	while (ft_space(data[*i]))
		(*i)++;
	return (token);
}

t_token	*handle_quotes(const char *data, int *i)
{
	t_token	*token;

	token = parse_quoted_token(data, i);
	if (!token)
		return (NULL);
	return (token);
}
