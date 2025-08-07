/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:00:50 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/04 16:32:15 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	my_env(t_env_list *env, int	*exit_st)
{
	while (env)
	{
		if (env->content.value)
			printf("%s=%s\n", env->content.key, env->content.value);
		env = env->next;
	}
	*exit_st = 0;
}
