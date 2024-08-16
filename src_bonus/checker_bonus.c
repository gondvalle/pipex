/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-val <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:36:23 by gdel-val          #+#    #+#             */
/*   Updated: 2024/07/22 19:36:25 by gdel-val         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**path_env(char **env)
{
	size_t	i;
	char	**paths;
	char	*src;

	i = where_path(env);
	src = env[i] + 5;
	paths = ft_split(src, ':');
	if (!paths)
		ft_error(MALLOC, NULL);
	return (paths);
}

char	*command(char **env, char *arg)
{
	char	*command;
	char	**path;
	char	*first;
	size_t	i;

	i = 0;
	path = path_env(env);
	first = first_word(arg);
	while (path[i] != NULL)
	{
		command = ft_threejoin(path[i], "/", first);
		if (access(command, F_OK | X_OK) == 0)
			return (ft_free(path), free(first), command);
		free(command);
		i++;
	}
	ft_free(path);
	ft_error(COMMAND, first);
	free(first);
	return (NULL);
}

void	here_doc(char **argv)
{
	char	*here;
	char 	*delimitier;
	int		in_fd;

	delimitier = ft_strjoin(argv[2], "\n");
	in_fd = open(".infd", O_CREAT | O_RDWR, 0644);
	if (in_fd == -1)
		ft_error("Error", NULL);
	while (1)
	{
		ft_putstr_fd(">", 0);
		here = get_next_line(0);
		if (ft_strncmp(here, delimitier, ft_strlen(here)) == 0)
		{
			free(delimitier);
			break ;
		}
		ft_putstr_fd(here, in_fd);
		free(here);
	}
	free(here);
	close(in_fd);
}

char **commands(t_arguments_bonus arguments, int argn, char **argv, char **env)
{
	char	**commands;
	int		i;

	i = -1;
	commands = ft_calloc(argn - 3 - arguments.here_doc + 1, sizeof(char *));
	while (++i < argn  - 3 - arguments.here_doc)
	{
		commands[i] = command(env, argv[i + 2 + arguments.here_doc]);
		if (!commands[i])
			return(ft_free(commands));
	}
	return (commands);
}

char ***splits(t_arguments_bonus arguments, int argn, char **argv)
{
	char	***splits;
	int		i;

	i = -1;
	splits = ft_calloc(argn - 3 - arguments.here_doc + 1, sizeof(char **));
	while (++i < argn  - 3 - arguments.here_doc)
	{
		splits[i] = ft_split(argv[i + 2 + arguments.here_doc], ' ');
		if (!splits[i])
		{
			while (i >= 0)
			{
				ft_free(splits[i]);
				i--;
			}
			ft_error(MALLOC, NULL);
			return (0);
		}
	}
	return (splits);
}

t_arguments_bonus	check_arg_bonus(int argn, char **argv, char **env)
{
	t_arguments_bonus arguments;

	arguments = check_here(argn, argv);
	arguments.out_fd = open(argv[argn - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (arguments.out_fd < 0)
		ft_error(FILE, argv[argn - 1]);
	arguments.commands = commands(arguments, argn, argv, env);
	arguments.splits = splits(arguments, argn, argv);
	arguments.argv = argv;
	return (arguments);
}

t_arguments_bonus	check_here(int argn, char **argv)
{
	t_arguments_bonus	arguments;

	if (argn < 5)
		ft_error(ARGUMENTS, NULL);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		here_doc(argv);
		arguments.in_fd = open(".infd", O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (arguments.in_fd == -1)
			ft_error("Error", NULL);
		arguments.here_doc = 1;
	}
	else
	{
		arguments.in_fd = open(argv[1], O_RDONLY);
		if (arguments.in_fd < 0)
			ft_error(FILE, argv[1]);
		arguments.here_doc = 0;
	}
	return (arguments);
}
