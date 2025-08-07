/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:38:46 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/04 14:00:30 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_special_dollar(char *s, int *i, int *exit_stat)
{
	char	*status;
	char	*temp;

	status = ft_itoa(*exit_stat);
	temp = ft_strjoin(s, status);
	free(s);
	free(status);
	*i += 2;
	return (temp);
}

char	*extract_var_value(char *str, int *i, t_env_list *env, char *s)
{
	char		*key;
	char		*temp;
	int			len;
	t_env_list	*tmp;

	len = 0;
	if (ft_isdigit(str[*i]))
		return (s = handle_digit_env(str, i, env, s));
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (s = ft_strjoin_free(s, "$"));
	while (ft_isalnum(str[*i + len]) || str[*i + len] == '_')
		len++;
	key = substr(str, *i, len);
	*i += len;
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->content.key, ft_strlen(tmp->content.key) + 1))
		{
			temp = ft_strjoin(s, tmp->content.value);
			return (free(key), free(s), temp);
		}
		tmp = tmp->next;
	}
	return (free(key), s);
}

char	*handle_empty_or_space_after_dollar(char *s, int *i, char next)
{
	char	*temp;

	temp = NULL;
	if (next == '$')
		temp = ft_strjoin(s, "$");
	else if (next == '?')
		temp = ft_strjoin(s, "?");
	free(s);
	(*i)++;
	return (temp);
}

char	*append_char_to_str(char *s, char c)
{
	char	*temp;
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	temp = ft_strjoin(s, buf);
	free(s);
	return (temp);
}

char	*get_value1(char *str, t_env_list *env, int *exit_stat)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '$' || str[i + 1] == '?'))
			s = handle_special_dollar(s, &i, exit_stat);
		else if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1]))
		{
			i++;
			s = extract_var_value(str, &i, env, s);
		}
		else if (str[i] == '$' && (str[i + 1] == '\0' || str[i + 1] == ' '))
			s = handle_empty_or_space_after_dollar(s, &i, '$');
		else if (str[i] == '?' && (str[i + 1] == '\0' || str[i + 1] == ' '))
			s = handle_empty_or_space_after_dollar(s, &i, '?');
		else
			s = append_char_to_str(s, str[i++]);
	}
	return (s);
}
