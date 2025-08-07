/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:57:49 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/05 20:06:33 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	chake_arg(char *str)
{
	int	i;

	if (str[0] <= '9' && str[0] >= '0')
		return (1);
	i = 1;
	while (str[i])
	{
		if (is_alpha(str[i]) == 0 && !(str[i] >= '0' && str[i] <= '9'))
			if (str[i] != '_')
				return (1);
		i++;
	}
	return (0);
}

void	delet_list(t_env_list **en, char *var, int start)
{
	t_env_list	*first;
	t_env_list	*therd;
	t_env_list	*env;

	env = *en;
	first = env;
	while (env && str_cmp(env->content.key, var) == 0)
	{
		env = env->next;
		start++;
	}
	while (first && first->next != env)
		first = first->next;
	if (env)
	{
		therd = env->next;
		env->next = NULL;
		free(env->content.key);
		free(env->content.value);
		free(env);
		if (first)
			first->next = therd;
		if (start == 0)
			*en = therd;
	}
}

void	my_unset(t_env_list **en, char **args, int *exit_st)
{
	int	i;

	i = 1;
	*exit_st = 0;
	while (args[i])
	{
		if (chake_arg(args[i]))
		{
			write_err("Minishell: unset: `", args[i],
				"': not a valid identifier\n");
			*exit_st = 1;
		}
		delet_list(en, args[i], 0);
		i++;
	}
}
