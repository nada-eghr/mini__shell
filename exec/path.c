/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:29:52 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/06 14:07:44 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_chr(char *cmd, char c)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	while (i >= 0)
	{
		if (cmd[i] == c)
			return (1);
		i--;
	}
	return (0);
}

char	*serch_path_env(char *cmd, t_env_list *env, int *exit_st)
{
	char	*path;
	char	**split_path;
	char	*new_p;
	int		i;

	i = 0;
	path = my_get_env("PATH", env);
	split_path = ft_split(path, ':');
	while (split_path[i])
	{
		new_p = ft_join_path(split_path[i], cmd, '/');
		if (access(new_p, X_OK) == 0)
			return (free(split_path), new_p);
		free(new_p);
		i++;
	}
	if (split_path)
		free(split_path);
	write_err("Minishell: ", cmd, ": command not found\n");
	return (*exit_st = CMD_NOTFIND, NULL);
}

char	*it_correct_comnd(int *exit_st, char *cmd, t_env_list *env)
{
	struct stat	sb;

	if (str_chr(cmd, '/'))
	{
		if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
		{
			write_err("Minishell: ", cmd, ": is a directory\n");
			return (*exit_st = 126, NULL);
		}
		if (access(cmd, X_OK) == 0)
			return (*exit_st = 0, cmd);
		else
		{
			write_err("Minishell: ", cmd, "p");
			return (*exit_st = 127, NULL);
		}
	}
	return (serch_path_env(cmd, env, exit_st));
}
