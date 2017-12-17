/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 16:56:39 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/15 19:47:56 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "mini.h"

static void	strip_unsupported(char *raw)
{
	int	i;

	while (*raw)
	{
		if (*raw == 0x1B)
		{
			i = 0;
			while (raw[i] && raw[i] != ' ')
				i++;
			ft_memset(raw, ' ', i);
			raw += i;
			continue ;
		}
		if (*raw == '\''
			|| *raw == '\"'
			|| *raw == '\\'
			|| *raw == '`'
			|| (*raw >= '\t' && *raw <= '\r'))
			*raw = ' ';
		raw++;
	}
}

t_bool		parse_args(t_shell *ms, char *raw)
{
	t_mchain	*mchain;

	if (!(mchain = ft_mcget("ms_argv")))
		mem_error();
	strip_unsupported(raw);
	ms->argv = tokenize(mchain, raw, ' ');
	if (!ms->argv[0])
		return (FALSE);
	expand_vars(ms->argv);
	return (TRUE);
}

char		**tokenize(t_mchain *mchain, char *raw, char delim)
{
	t_mlink		*mlink;

	while (*raw)
	{
		while (*raw == delim)
			*raw++ = '\0';
		if (*raw)
			ft_mlappend(mchain, raw, 0);
		while (*raw && *raw != delim)
			raw++;
	}
	if (!ft_mlarray(mchain))
		mem_error();
	mlink = mchain->start->next;
	while (mlink)
		mlink = ft_mlremove(mlink);
	return (mchain->start->ptr);
}
