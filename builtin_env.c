/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 14:54:20 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/15 14:06:47 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mini.h"

static t_bool	valid_key(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (!env_char(key[i], i))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool			benv(t_shell *ms)
{
	char	**env;

	env = ms->env;
	while (*env)
	{
		write(1, *env, ft_strlen(*env));
		write(1, "\n", 1);
		env++;
	}
	return (TRUE);
}

t_bool			bsetenv(t_shell *ms)
{
	char	**argv;
	int		i;

	argv = ms->argv;
	i = 0;
	while (argv[i])
		i++;
	if (i > 3)
		return (berror("setenv", "too many arguments", NULL, 1));
	if (i == 1)
		return (benv(ms));
	if (!valid_key(argv[1]))
		return (berror("setenv", "invalid parameter name", argv[1], 1));
	if (i < 3)
		set_env(ms, argv[1], "");
	else
		set_env(ms, argv[1], argv[2]);
	return (TRUE);
}

t_bool			bunsetenv(t_shell *ms)
{
	char	**argv;
	int		i;

	if (!(argv = ms->argv)[1])
		return (berror("unsetenv", "too few arguments", NULL, 1));
	i = 1;
	while (argv[i])
		unset_env(ms, argv[i++]);
	return (TRUE);
}
