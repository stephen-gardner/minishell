/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:54:24 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/16 01:22:05 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "mini.h"

static t_mlink	*find_env(t_mchain *mchain, char *key, int key_len)
{
	t_mlink	*mlink;
	char	*pair;
	int		i;

	mlink = mchain->start;
	while (mlink)
	{
		i = 0;
		pair = mlink->ptr;
		while (i < key_len && pair[i])
		{
			if (pair[i] != key[i])
				break ;
			i++;
		}
		if (i == key_len && pair[i] == '=')
			break ;
		mlink = mlink->next;
	}
	return (mlink);
}

char			*get_env(char *key)
{
	t_mlink	*mlink;
	int		key_len;

	key_len = ft_strlen(key);
	mlink = find_env(ft_mcget("ms_env"), key, key_len);
	return ((mlink) ? mlink->ptr + key_len + 1 : "");
}

void			load_env(t_shell *ms, char **env)
{
	t_mchain	*mchain;
	char		*var;

	if (!(mchain = ft_mcget("ms_env")))
		mem_error();
	while (*env)
	{
		if (!(var = ft_strdup(*env++)) || !ft_mlappend(mchain, var, 0))
			mem_error();
	}
	if (!ft_mlarray(mchain))
		mem_error();
	ms->env = mchain->start->ptr;
}

void			set_env(t_shell *ms, char *key, char *val)
{
	t_mchain	*mchain;
	t_mlink		*mlink;
	char		*pair;
	char		*tmp;
	int			key_len;

	key_len = ft_strlen(key);
	if (!(pair = (char *)malloc(key_len + ft_strlen(val) + 2)))
		mem_error();
	tmp = ft_stpcpy(pair, key);
	*tmp++ = '=';
	ft_stpcpy(tmp, val);
	mchain = ft_mcget("ms_env");
	if ((mlink = find_env(mchain, key, key_len)))
	{
		free(mlink->ptr);
		mlink->ptr = pair;
	}
	else if (!ft_mlappend(mchain, pair, 0))
		mem_error();
	ft_mlpop(mchain);
	if (!ft_mlarray(mchain))
		mem_error();
	ms->env = mchain->start->ptr;
}

void			unset_env(t_shell *ms, char *key)
{
	t_mchain	*mchain;
	t_mlink		*mlink;

	mchain = ft_mcget("ms_env");
	if (!(mlink = find_env(mchain, key, ft_strlen(key))))
		return ;
	ft_mlpop(mchain);
	ft_mldel(mlink);
	if (!ft_mlarray(mchain))
		mem_error();
	ms->env = mchain->start->ptr;
}
