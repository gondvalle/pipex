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

void	child_one(t_arguments arguments, int *fds, char **argv, char **env)
{
	close(fds[READ]);
	if (dup2(arguments.in_fd, STDIN_FILENO) == -1)
		ft_error(DUP, NULL);
	if (dup2(fds[WRITE], STDOUT_FILENO) == -1)
		ft_error(DUP, NULL);
	close(fds[WRITE]);
	close(arguments.in_fd);
	if (execve(arguments.command_one, arguments.split_one, env) == -1)
		ft_error(COMMAND, argv[2]);
}

void	child_two(t_arguments arguments, int *fds, char **argv, char **env)
{
	close(fds[WRITE]);
	if (dup2(arguments.out_fd, STDOUT_FILENO) == -1)
		ft_error(DUP, NULL);
	if (dup2(fds[READ], STDIN_FILENO) == -1)
		ft_error(DUP, NULL);
	close(fds[READ]);
	close(arguments.out_fd);
	if (execve(arguments.command_two, arguments.split_two, env) == -1)
		ft_error(COMMAND, argv[3]);
}

void	ft_free_arguments(t_arguments arguments)
{
	free(arguments.command_one);
	free(arguments.command_two);
	ft_free(arguments.split_one);
	ft_free(arguments.split_two);
}

void	ft_close(int *fds, t_arguments	arguments)
{
	close(fds[READ]);
	close(fds[WRITE]);
	close(arguments.in_fd);
	close(arguments.out_fd);
}

int	main(int argn, char **argv, char **env)
{
	t_arguments	arguments;
	pid_t		pid[2];
	int			fds[2];

	arguments = check_arg(argn, argv, env);
	if (pipe(fds) == -1)
		ft_error(PIPE, NULL);
	pid[0] = fork();
	if (pid[0] == -1)
		ft_error(FORK, NULL);
	if (pid[0] == 0)
		child_one(arguments, fds, argv, env);
	pid[1] = fork();
	if (pid[1] == -1)
		ft_error(FORK, NULL);
	if (pid[1] == 0)
		child_two(arguments, fds, argv, env);
	ft_close(fds, arguments);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	ft_free_arguments(arguments);
	return (0);
}
