/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-val <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:37:47 by gdel-val          #+#    #+#             */
/*   Updated: 2024/04/23 16:37:49 by gdel-val         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>
# include <sys/wait.h>

# define READ 0
# define WRITE 1

# define FILE "bash: no such file or directory: "
# define COMMAND "bash: command not found: "
# define ARGUMENTS "Error: bad number of arguments\n"
# define CHILD "child error"
# define PIPE "pipe error"
# define MALLOC "memory error"
# define FORK "fork error"
# define DUP "dup error"
# define WAIT "waitpid error"

typedef struct s_arguments
{
	int		in_fd;
	char	*command_one;
	char	*command_two;
	char	**split_one;
	char	**split_two;
	int		out_fd;
}				t_arguments;

typedef struct s_arguments_bonus
{
	int		in_fd;
	char	**commands;
	char	***splits;
	int		out_fd;
	int		here_doc;
	char	**argv;
}				t_arguments_bonus;

char		**ft_free(char **mat);
void		ft_error(char *str, char *file);
char		*ft_threejoin(char const *s1, char const *s2, char const *s3);
size_t		where_path(char **env);
char		*first_word(char *arg);
char		*command(char **env, char *arg);
t_arguments	check_arg(int argn, char **argv, char **env);

t_arguments_bonus	check_here(int argn, char **argv);
t_arguments_bonus	check_arg_bonus(int argn, char **argv, char **env);

void print_arguments_bonus(t_arguments_bonus *args);
void free_arguments_bonus(t_arguments_bonus *args);

#endif