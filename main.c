/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 00:12:30 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/16 00:48:38 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "get_next_line.h"
#include "mini.h"

static t_shell	*get_shell(char **env)
{
	static t_shell	*ms;

	if (!ms)
	{
		if (!(ms = (t_shell *)ft_memalloc(sizeof(t_shell))))
			mem_error();
		load_env(ms, env);
	}
	return (ms);
}

static void		handle_sigint(int sig)
{
	UNUSED(sig);
	if (!ft_mcexists("ms_lock"))
	{
		ft_memdel(ft_mcget("ms_buffer")->start->ptr);
		write(1, "\n$> ", 4);
	}
}

static void		run_commands(t_shell *ms, char *raw)
{
	t_mchain	*mchain;
	char		**commands;
	int			i;

	if (!(mchain = ft_mcget("ms_cmd")))
		mem_error();
	commands = tokenize(mchain, raw, ';');
	i = 0;
	while (commands[i])
	{
		if (*commands[i] && parse_args(ms, commands[i]))
		{
			dispatch(ms);
			while (*(ms->argv + 1))
				ms->argv++;
			set_env(ms, "_", *ms->argv);
		}
		ms->argv = NULL;
		ms->target = NULL;
		ft_mcdel(ft_mcget("ms_argv"));
		i++;
	}
	ft_mcdel(mchain);
	free(raw);
}

int				main(int ac, char **av, char **env)
{
	t_shell	*ms;
	char	*raw;
	int		res;

	UNUSED(ac);
	UNUSED(av);
	ms = get_shell(env);
	if (!ft_mladd(ft_mcget("ms_buffer"), &raw, 0))
		mem_error();
	signal(SIGINT, &handle_sigint);
	while (TRUE)
	{
		write(1, "$> ", 3);
		if ((res = get_next_line(0, &raw)) < 0)
			continue ;
		if (res == 0)
			exit_shell(0);
		run_commands(ms, raw);
	}
	return (0);
}
