/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 20:03:11 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/15 23:20:28 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "mini.h"

static void	ms_wait(void)
{
	t_mchain	*mchain;
	int			status;

	if (!(mchain = ft_mcget("ms_lock")))
		mem_error();
	wait(&status);
	if (WIFSIGNALED(status))
		write(1, "\n", 1);
	ft_mcdel(mchain);
}

t_bool		find_app(t_shell *ms, char *path)
{
	struct stat	*stats;

	if (access(path, F_OK) < 0)
		return (FALSE);
	if (!(stats = (struct stat *)ft_memalloc(sizeof(struct stat))))
		mem_error();
	if (access(path, X_OK) < 0
		|| stat(path, stats) < 0
		|| (stats->st_mode & S_IFMT) == S_IFDIR)
	{
		print_error("permission denied", path, 0);
		free(stats);
		return (TRUE);
	}
	ms->target = path;
	free(stats);
	return (TRUE);
}

t_bool		find_path_app(t_shell *ms, char *paths, char *name)
{
	t_mchain	*mchain;
	char		*app_path;
	int			n;

	mchain = ft_mcget("ms_argv");
	while (paths && *paths)
	{
		n = 0;
		while (paths[n] && paths[n] != ':')
			n++;
		if (!(app_path = ft_mlalloc(mchain, n + ft_strlen(name) + 2)))
			mem_error();
		ft_memcpy(app_path, paths, n);
		app_path[n] = '/';
		ft_stpcpy(app_path + n + 1, name);
		if (find_app(ms, app_path))
			return ((ms->target) ? TRUE : FALSE);
		paths += n + (*(paths + n) == ':');
		ft_mlpop(mchain);
	}
	print_error("command not found", name, 0);
	return (FALSE);
}

void		dispatch(t_shell *ms)
{
	char	**argv;

	argv = ms->argv;
	if (find_builtin(ms))
		return ;
	if (*argv[0] != '.' && *argv[0] != '/')
		find_path_app(ms, get_env("PATH"), argv[0]);
	else
	{
		if (*argv[0] == '.' && *(argv[0] + 1) != '/')
			print_error("command not found", argv[0], 0);
		else if (!find_app(ms, argv[0]))
			print_error("no such file or directory", argv[0], 0);
	}
	if (!ms->target)
		return ;
	if (fork())
		ms_wait();
	else
		execve(ms->target, ms->argv, ms->env);
}
