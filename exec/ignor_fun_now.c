/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignor_fun_now.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:42:51 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/05 18:57:43 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	serch_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i > 0)
		str[i] = '\0';
	return (i);
}

char	*new_tab(t_env_list *list_env)
{
	char	*arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	arr = malloc(ft_strlen(list_env->content.key) 
			+ ft_strlen(list_env->content.value) + 2);
	while (list_env->content.key[i])
	{
		arr[i] = list_env->content.key[i];
		i++;
	}
	if (list_env->content.value)
	{
		arr[i++] = '=';
		while (list_env->content.value[j])
			arr[i++] = list_env->content.value[j++];
		arr[i] = '\0';
	}
	return (arr);
}

char	**return_list_to_arg(t_env_list *list_env)
{
	t_env_list	*l;
	char		**arg;
	int			i;
	int			j;

	i = 0;
	j = 0;
	l = list_env;
	while (l)
	{
		i++;
		l = l->next;
	}
	l = list_env;
	arg = malloc(sizeof(char *) * (i + 1));
	while (j < i && list_env)
	{
		arg[j] = new_tab(list_env);
		list_env = list_env->next;
		j++;
	}
	arg[j] = NULL;
	return (arg);
}
