/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 13:27:13 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/11 13:45:32 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "mini.h"

void			exit_shell(int code)
{
	write(1, "exit\n", 5);
	exit(code);
}

t_bool			bexit(t_shell *ms)
{
	char	**argv;
	int		code;
	int		sign;
	int		i;

	argv = ms->argv;
	i = 0;
	while (argv[i])
		i++;
	if (i > 2)
		return (berror("exit", "too many arguments", NULL, 1));
	if (i == 1)
		exit_shell(0);
	sign = (argv[1][0] == '-') ? -1 : 1;
	i = (sign < 0) ? 1 : 0;
	code = 0;
	while (argv[1][i])
	{
		if ((unsigned int)(argv[1][i] - '0') > 9)
			return (berror("exit", "expression syntax", NULL, 1));
		code += (code * 10) + ((argv[1][i++]) - '0');
	}
	exit_shell(code);
	return (TRUE);
}
