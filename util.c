/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 04:24:37 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/16 01:12:40 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mini.h"

int				berror(char *prefix, char *err, char *arg, int rval)
{
	write(2, prefix, ft_strlen(prefix));
	write(2, ": ", 2);
	write(2, err, ft_strlen(err));
	if (arg)
	{
		write(2, ": ", 2);
		write(2, arg, ft_strlen(arg));
	}
	write(2, "\n", 1);
	return (rval);
}

char			*build_path(char *parent, char *child)
{
	char	*path;
	char	*tmp;
	int		len;

	len = ft_strlen(parent) + 1 + ft_strlen(child);
	if (!(path = ft_mlalloc(ft_mcget("ms_argv"), len + 1)))
		mem_error();
	tmp = ft_stpcpy(path, parent);
	if (*(tmp - 1) != '/')
		*tmp++ = '/';
	if (*child == '/')
		child++;
	tmp = ft_stpcpy(tmp, child);
	return (path);
}

t_bool			env_char(char c, int i)
{
	return (c == '_'
		|| ((unsigned int)(c - '0') < 10 && i != 0)
		|| ((unsigned int)(c - 'A') < 26)
		|| ((unsigned int)(c - 'a') < 26));
}

void			mem_error(void)
{
	print_error("cannot allocate memory", NULL, 1);
	exit_shell(1);
}

int				print_error(char *err, char *arg, int rval)
{
	return (berror("minishell", err, arg, rval));
}
