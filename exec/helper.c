/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:26:29 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/06 14:12:48 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_env_list *env)
{
	t_env_list	*list;

	while (env)
	{
		list = env;
		env = env->next;
		list->next = NULL;
		free(list->content.key);
		free(list->content.value);
	}
	env = NULL;
}

void	free_all(char **s1, void *s2, int ext)
{
	int	i;

	i = 0;
	if (s1)
		while (s1[i])
			free(s1[i++]);
	if (s2)
		free(s2);
	exit(ext);
}

char	*ft_join_path(char *s1, char *s2, char sep)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!str)
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	if (sep == '/')
		str[j++] = '/';
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

int	str_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}

t_env_list	*get_list_env(char **env)
{
	t_env_list	*new_env;
	t_env_list	*serch;
	int			i;
	int			serch_old_p;

	i = 1;
	serch_old_p = 0;
	new_env = ft_lstnew_env(env[0]);
	while (env[i])
		ft_lstadd_back(&new_env, ft_lstnew_env(env[i++]));
	serch = new_env;
	while (serch)
	{
		if (str_cmp(serch->content.key, "OLDPWD"))
		{
			free(serch->content.value);
			serch->content.value = NULL;
			serch_old_p = 1;
		}
		serch = serch->next;
	}
	if (serch_old_p == 0)
		ft_lstadd_back(&new_env, ft_lstnew_env("OLDPWD"));
	return (new_env);
}
