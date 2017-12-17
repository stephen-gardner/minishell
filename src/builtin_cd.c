/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:16:41 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/16 15:59:11 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "mini.h"

static int		cderror(char *err, char *arg, int rval)
{
	return (berror("cd", err, arg, rval));
}

static t_bool	check_folder(char *path)
{
	struct stat	*stats;

	if (!(stats = ft_mlalloc(ft_mcget("ms_argv"), sizeof(struct stat))))
		mem_error();
	if (access(path, F_OK) < 0)
		return (cderror("no such file or directory", path, 0));
	if (stat(path, stats) < 0)
		return (cderror("permission denied", path, 0));
	if ((stats->st_mode & S_IFMT) != S_IFDIR)
		return (cderror("not a directory", path, 0));
	if (access(path, X_OK) < 0)
		return (cderror("permission denied", path, 0));
	return (TRUE);
}

static void		print_path(char *path)
{
	char	*home;
	int		home_len;

	home = get_env("HOME");
	home_len = ft_strlen(home);
	if (!strncmp(path, home, home_len))
	{
		write(1, "~", 1);
		if (*(path + home_len) && *(path + home_len) != '/')
			write(1, "/", 1);
		write(1, path + home_len, ft_strlen(path + home_len));
	}
	else
		write(1, path, ft_strlen(path));
	write(1, "\n", 1);
}

static char		*change_dir(t_shell *ms, char *path, char *old_prev)
{
	char	*new_prev;
	char	*pwd;

	if (!(new_prev = getcwd(NULL, 0)))
		mem_error();
	chdir(path);
	if (path == old_prev)
		print_path(path);
	if (!(pwd = getcwd(NULL, 0)))
		mem_error();
	set_env(ms, "PWD", pwd);
	set_env(ms, "OLDPWD", new_prev);
	free(pwd);
	free(old_prev);
	return (new_prev);
}

t_bool			bcd(t_shell *ms)
{
	char		**argv;
	static char	*prev;
	char		*path;
	int			i;

	prev = (prev) ? prev : ft_strdup(get_env("HOME"));
	if (!prev || (!*prev && !(prev = ft_strdup("/"))))
		mem_error();
	argv = ms->argv;
	i = 0;
	while (argv[i])
		i++;
	if (i > 2)
		return (cderror("too many arguments", NULL, 1));
	path = (i == 1) ? get_env("HOME") : NULL;
	if (!path)
		path = (!ft_strcmp(argv[1], "-")) ? prev : argv[1];
	if (!check_folder(path))
		return (TRUE);
	prev = change_dir(ms, path, prev);
	return (TRUE);
}
