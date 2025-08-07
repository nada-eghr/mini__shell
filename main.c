/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:27:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/06 18:25:43 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int sigg = 0;

void	handler(int s)
{
	(void)s;
	sigg = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay(); 
	return ;
}

void	defult_env(t_env_list **env)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = getcwd(NULL, 0);
	*env = ft_lstnew_env(ft_strjoin("PATH=", pwd));
	free(pwd);
	ft_lstadd_back(&*env, ft_lstnew_env(ft_strjoin("SHLVL=", "1")));
	ft_lstadd_back(&*env, ft_lstnew_env(ft_strjoin("_=", "/usr/bin/env")));
	ft_lstadd_back(&*env, ft_lstnew_env(ft_strjoin("OLDPWD", NULL)));
}

void	input_chack(char *input, t_env_list *env_list, t_var *var)
{
	if (sigg != NO_SIG_NAL)
	{
		var->exit_stat = sigg;
		sigg = NO_SIG_NAL;
	}
	if (!input)
	{
		write(1, "exit\n", 5);
		free_env(env_list);
		exit (var->exit_stat);
	}
}
t_token	*start_pars(t_vmin *v, t_var *var, int *continu, t_env_list *env_list)
{
	t_token	*tokens;
	char	*input;

	v->cont = 0;
	input = readline("minishell$ ");
	input_chack(input, env_list, var);
	if (is_line_empty(input))
		return (*continu = 1, free(input), NULL);
	add_history(input);
	if (check_quotes(input, &*var))
		return (*continu = 1, free(input), NULL);
	tokens = convert_to_node(input);
	if (!tokens)
		return (*continu = 1, free(tokens), NULL);
	free(input);
	return (expand_token(tokens, env_list, &var->exit_stat));
}

void	first_step(char **env, t_vmin *v)
{
	sigg = NO_SIG_NAL;
	if (!env[0])
		defult_env(&v->env_list);
	else
		v->env_list = get_list_env(env);
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal (SIGINT, handler);
	sigg = NO_SIG_NAL;
	v->var.exit_stat = 0;
}
void ll(void)
{
	system("leaks -q minishell");
}
int	main(int ac, char **av, char **env)
{
	t_vmin	v;
atexit(ll);
	(void)ac;
	(void)av;
	first_step(env, &v);
	while (1)
	{
		v.filter_lst = start_pars(&v, &v.var, &v.cont, v.env_list);
		if (!v.filter_lst && v.cont == 1)
			continue ;
		v.second_tokens = second_tokinization(v.filter_lst);
		free_list(v.filter_lst);
		v.second_tokens_head = v.second_tokens;
		remove_empty_node(&v.second_tokens);
		if (check_error(&v.second_tokens, &v.var) == 1)
		{
			free_second_tokens(&v.second_tokens_head);
			continue ;
		}
		v.cmd = list_cmd(v.second_tokens);
		exc(v.cmd, &v.env_list, &v.var);
		free_list1(v.second_tokens);
		free_cmd_list(&v);
	}
	return (0);
}
