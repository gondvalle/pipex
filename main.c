/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-val <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:37:45 by gdel-val          #+#    #+#             */
/*   Updated: 2024/04/17 20:37:51 by gdel-val         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// void	ft_leaks(void)
// {
// 	system("leaks -q pipex");
// }
// atexit(ft_leaks);

size_t	where_path(char **env)
{
	size_t	i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		i++;
	return (i);
}

char	**path_env(char **env)
{
	size_t  i;
	char **paths;
	char *src;

	i = where_path(env);
	src = env[i] + 5;
	paths = ft_split(src, ':');
	if (!paths)
		ft_error(MALLOC, NULL);
	return (paths);
}

char	*first_word(char *arg)
{
	char	*word;
	char	**complete;

	complete = ft_split(arg, ' ');
	if (!complete)
		ft_error(MALLOC, NULL);
	word = ft_strdup(complete[0]);
	if (!word)
		ft_error(MALLOC, NULL);
	ft_free(complete);
	return (word);
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
	while(path[i] != NULL)
	{
		command = ft_threejoin(path[i], "/", first);
		if (!command)
			ft_error(MALLOC, NULL);
		if (access(command, F_OK | X_OK) == 0)
			return (ft_free(path), free(first), command);
		i++;
	}
	ft_error(COMMAND, first);
	return (NULL);
}
void	check_arg(int argn, char **argv, char **env)
{
	int		int_fd;
	int		out_fd;
	char	*arg_one;
	char	*arg_two;

	if (argn != 5)
		ft_error(ARGUMENTS, NULL);
	int_fd = open(argv[1], O_RDONLY);
	if (int_fd < 0)
		ft_error(FILE, argv[1]);
	out_fd = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY);
	if (out_fd < 0)
		ft_error(FILE, argv[4]);
	arg_one = command(env, argv[2]);
	arg_two = command(env, argv[3]);
	free(arg_one);
	free(arg_two);
}

int	main(int argn, char **argv, char **env)
{
	int		int_fd;
	int		out_fd;
	char	*command_child;
	char 	*command_parent;
	char	**arg1;
	char	**arg2;

	check_arg(argn, argv, env);
	command_child = command(env, argv[2]);
	arg1 = ft_split(argv[2], ' ');
	if (!arg1)
		ft_error(MALLOC, NULL);
	execve(command_child, arg1, env);
	command_parent = command(env, argv[3]);
	printf("%s\n", command_child);
	free(command_child);
	free(command_parent);
	close(int_fd);
}
