/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 17:17:12 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/15 19:36:52 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H
# include "ft_memmgr.h"

# include <stdio.h>

typedef struct	s_shell
{
	char	**env;
	char	**argv;
	char	*target;
}				t_shell;

typedef struct	s_builtin
{
	char	*label;
	t_bool	(*execute)(t_shell *);
}				t_builtin;

/*
** builtin_cd.c
*/

t_bool			bcd(t_shell *ms);

/*
** builtin_echo.c
*/

t_bool			becho(t_shell *ms);

/*
** builtin_env.c
*/

t_bool			benv(t_shell *ms);
t_bool			bsetenv(t_shell *ms);
t_bool			bunsetenv(t_shell *ms);

/*
** builtin_exit
*/

void			exit_shell(int code);
t_bool			bexit(t_shell *ms);

/*
** builtins.c
*/

t_bool			find_builtin(t_shell *ms);

/*
** env.c
*/

void			load_env(t_shell *ms, char **env);
char			*get_env(char *key);
void			set_env(t_shell *ms, char *key, char *val);
void			unset_env(t_shell *ms, char *key);

/*
** execute.c
*/

t_bool			find_app(t_shell *ms, char *path);
t_bool			find_path_app(t_shell *ms, char *paths, char *name);
void			dispatch(t_shell *ms);

/*
** parse.c
*/

t_bool			parse_args(t_shell *mas, char *raw);
char			**tokenize(t_mchain *mchain, char *raw, char delim);

/*
** util.c
*/

int				berror(char *prefix, char *err, char *arg, int rval);
char			*build_path(char *parent, char *child);
t_bool			env_char(char c, int i);
void			mem_error(void);
int				print_error(char *err, char *arg, int rval);

/*
** vars.c
*/

void			expand_vars(char **argv);
#endif
