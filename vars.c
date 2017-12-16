/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 16:09:02 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/16 01:21:35 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mini.h"

static char	*build_arg(t_mchain *mchain)
{
	t_mlink	*mlink;
	char	*res;
	int		len;

	len = 0;
	mlink = mchain->start;
	while (mlink)
	{
		len += mlink->size;
		mlink = mlink->next;
	}
	if (!(res = ft_mlalloc(ft_mcget("ms_argv"), len + 1)))
		mem_error();
	len = 0;
	mlink = mchain->start;
	while (mlink)
	{
		ft_memcpy(res + len, mlink->ptr, mlink->size);
		len += mlink->size;
		mlink = ft_mlremove(mlink);
	}
	res[len] = '\0';
	return (res);
}

static void	expand_home_path(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (*argv[i] == '~')
		{
			if (*(argv[i] + 1) == '/' || !*(argv[i] + 1))
				argv[i] = build_path(get_env("HOME"), argv[i] + 1);
			else
				argv[i]++;
		}
		i++;
	}
}

static void	process_var(t_mchain *mchain, char **arg, int *i)
{
	char		*pos;
	char		*key;
	char		*var;
	int			len;

	pos = *arg + *i + 1;
	len = 0;
	while (env_char(pos[len], len))
		len++;
	if (!(key = ft_strndup(pos, len)) || !ft_mlappend(mchain, *arg, *i))
		mem_error();
	if ((var = get_env(key)) && !ft_mlappend(mchain, var, ft_strlen(var)))
		mem_error();
	*arg += *i + 1 + len;
	*i = 0;
	free(key);
}

static char	*process_arg(char *arg)
{
	t_mchain	*mchain;
	char		*res;
	int			i;

	res = NULL;
	if (!(mchain = ft_mcget("ms_build")))
		mem_error();
	i = 0;
	while (arg[i])
	{
		while (arg[i] && arg[i] != '$')
			i++;
		if (arg[i] && arg[i + 1])
			process_var(mchain, &arg, &i);
	}
	if (mchain->link_count)
	{
		if (i && !ft_mlappend(mchain, arg, i))
			mem_error();
		res = build_arg(mchain);
	}
	ft_mcdel(mchain);
	return (res);
}

void		expand_vars(char **argv)
{
	char	*res;
	int		i;

	i = 0;
	while (argv[i])
	{
		if ((res = process_arg(argv[i])))
			argv[i] = res;
		i++;
	}
	expand_home_path(argv);
}
