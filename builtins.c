/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 23:16:36 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/12 07:00:00 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mini.h"

t_bool	find_builtin(t_shell *ms)
{
	static t_builtin	builtins[] = {
		{ "cd", &bcd },
		{ "echo", &becho },
		{ "exit", &bexit },
		{ "env", &benv },
		{ "setenv", &bsetenv },
		{ "unsetenv", &bunsetenv },
	};
	static int			size = sizeof(builtins) / sizeof(t_builtin);
	int					i;

	i = 0;
	while (i < size)
	{
		if (!ft_strcmp(ms->argv[0], builtins[i].label))
			return (builtins[i].execute(ms));
		i++;
	}
	return (FALSE);
}
