/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:11:49 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/06 14:08:29 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_od_nw_pwd(t_env_list *env, char *s)
{
	while (env && str_cmp(env->content.key, s) == 0)
		env = env->next;
	if (env)
	{
		free(env->content.value);
		env->content.value = getcwd(NULL, 0);
	}
}

void	my_cd(t_env_list *env, char **arg, int *exit_st)
{
	char	*path;
	int		er;

	update_od_nw_pwd(env, "OLDPWD");
	if (arg[1] == NULL)
	{
		path = my_get_env("HOME", env);
		if (!path)
			write (2, "Minishell: cd: HOME not set\n", 24);
		er = chdir(path);
		if (er != 0)
			perror("cd");
		if (!path || er != 0)
			*exit_st = 1;
		return ;
	}
	if (chdir(arg[1]) != 0)
	{
		write_err("Minishell: cd: ", arg[1], "p");
		*exit_st = 1;
		return ;
	}
	update_od_nw_pwd(env, "PWD");
	*exit_st = 0;
}
