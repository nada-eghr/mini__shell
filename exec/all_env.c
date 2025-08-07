/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:51:35 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/05 12:28:04 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char *data, int i)
{
	char	*line;
	int		j;

	j = 0;
	line = malloc(i + 1);
	while (j < i)
	{
		line[j] = data[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*get_line(char *data, char c)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (data[i] && data[i] != '=')
		i++;
	if (c == 'f')
		return (get_key(data, i));
	else if (data[i] && c == 'l')
	{
		if (data[i] == '=')
			i++;
		line = malloc(ft_strlen(&data[i]) + 1);
		while (data[i])
			line[j++] = data[i++];
		line[j] = '\0';
		return (line);
	}
	return (NULL);
}

t_env_list	*ft_lstnew_env(void *content)
{
	t_env_list	*nod;
	char		*frst;
	char		*last;

	frst = get_line(content, 'f');
	last = get_line(content, 'l');
	nod = malloc(sizeof(t_env_list));
	if (!nod)
		return (NULL);
	nod->content.key = frst;
	nod->content.value = last;
	nod->next = NULL;
	return (nod);
}

void	ft_lstadd_back(t_env_list **lst, t_env_list *n)
{
	t_env_list	*list;

	if (!lst || !n)
		return ;
	list = *lst;
	if (*lst == NULL)
	{
		*lst = n;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = n;
}

char	*my_get_env(char *str, t_env_list *env)
{
	while (env)
	{
		if (str_cmp(str, env->content.key))
			return (env->content.value);
		env = env->next;
	}
	return (NULL);
}
