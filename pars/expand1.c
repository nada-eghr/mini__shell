/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:25:38 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/01 13:40:26 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_quoted_text(char *str, int *i, char **s)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
		*s = append_char_to_str(*s, str[(*i)++]);
	if (str[*i] == quote)
		(*i)++;
}

char	*join_empty_and_skip(char *str, int *i, char *s)
{
	while (str[*i] && str[*i] != '$' && str[*i] != ' ')
		(*i)++;
	free(s);
	return (ft_strjoin("", ""));
}

char	*get_env_or_empty(char *key, t_env_list *env, int *exit_stat)
{
	char	*new_data;
	char	*value;

	new_data = get_value1(key, env, exit_stat);
	if (new_data)
		value = ft_strdup(new_data);
	else
		value = ft_strdup("");
	free(new_data);
	return (value);
}

void	expand_env_variable(t_token *tmp, t_env_list *env, int *exit_stat)
{
	int		j;
	char	*s1;
	char	*s2;
	char	*val;
	char	*joined;

	j = 0;
	while (tmp->token[j] && tmp->token[j] != '$')
		j++;
	s1 = substr(tmp->token, 0, j);
	s2 = substr(tmp->token, j, ft_strlen(tmp->token) - j);
	val = get_env_or_empty(s2, env, exit_stat);
	joined = ft_strjoin(s1, val);
	free(tmp->token);
	tmp->token = ft_strdup(joined);
	free(s1);
	free(s2);
	free(val);
	free(joined);
}

void	remove_quotes(t_token *tmp)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(ft_strlen(tmp->token) + 1);
	i = 0;
	j = 0;
	while (tmp->token[i])
	{
		if (tmp->token[i] != '"')
			str[j++] = tmp->token[i];
		i++;
	}
	str[j] = '\0';
	free(tmp->token);
	tmp->token = ft_strdup(str);
	free(str);
}
