/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gvalue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:31:03 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/04 14:01:22 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

char	*handle_digit_env(const char *str, int *i, t_env_list *env, char *s)
{
	char		buf[2];
	t_env_list	*tmp;
	char		*temp;

	if (!ft_isdigit(str[*i]))
		return (s);
	buf[0] = str[*i];
	buf[1] = '\0';
	(*i)++;
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content.key, buf, 2) == 0)
		{
			temp = ft_strjoin(s, tmp->content.value);
			free(s);
			return (temp);
		}
		tmp = tmp->next;
	}
	return (s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*substr(const char *src, int start, int len)
{
	char	*res;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strncpy(res, src + start, len);
	res[len] = '\0';
	return (res);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*cp;

	i = 0;
	if (!s)
		return (NULL);
	cp = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!cp)
		return (NULL);
	while (s[i])
	{
		cp[i] = s[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}
