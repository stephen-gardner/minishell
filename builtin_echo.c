/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 06:25:20 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/12 06:25:32 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mini.h"

t_bool	becho(t_shell *ms)
{
	char	**argv;
	int		i;
	int		nl;

	argv = ms->argv;
	i = 1;
	if (argv[i] && !ft_strcmp(argv[i], "-n"))
	{
		nl = 0;
		i++;
	}
	else
		nl = 1;
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (TRUE);
}
