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

void print_pipe_content(int fd_read)
{
	char *line;

	// Leer línea por línea del descriptor de archivo
	while ((line = get_next_line(fd_read)) != NULL)
	{
		// Imprimir la línea leída
		printf("%s", line);
		// Liberar la memoria asignada para la línea por get_next_line
		free(line);
	}

	// Cerrar el descriptor de archivo después de la lectura
	close(fd_read);
}

void	child_first(t_arguments_bonus arguments, int *fds, char **env)
{
	close(fds[READ]);
	if (dup2(arguments.in_fd, STDIN_FILENO) == -1)
		ft_error(DUP, NULL);
	if (dup2(fds[WRITE], STDOUT_FILENO) == -1)
		ft_error(DUP, NULL);
	close(fds[WRITE]);close(arguments.in_fd);
	if (execve(arguments.commands[0], arguments.splits[0], env) == -1)
		ft_error(COMMAND, arguments.argv[2 + arguments.here_doc]);
}

void	child_last(t_arguments_bonus arguments, int **fds, char **env, int argn)
{
	int	last;

	last = argn - 3 - arguments.here_doc - 2;
	printf("\nExecuting command %d: %s\n", last + 1, arguments.commands[last + 1]);
	printf("fds[last: %d][READ] = %d\n", last, fds[last][READ]);
	close(fds[last][WRITE]);
	if (dup2(fds[last][READ], STDIN_FILENO) == -1)
		ft_error(DUP, NULL);
	close(fds[last][READ]);
	if (dup2(arguments.out_fd, STDOUT_FILENO) == -1)
		ft_error(DUP, NULL);
	close(arguments.out_fd);
	if (execve(arguments.commands[last + 1], arguments.splits[last + 1], env) == -1)
		ft_error(COMMAND, arguments.argv[last + 3]);
}

void exec_commands(t_arguments_bonus arguments, int **fds, char **env, int i)
{
	printf("\nExecuting command %d: %s\n", i, arguments.commands[i]);
	printf("fds[%d][READ] = %d\n", i - 1, fds[i - 1][READ]);
	printf("fds[%d][WRITE] = %d\n", i, fds[i][WRITE]);
	close(fds[i][READ]);
	close(fds[i - 1][WRITE]);
	if (dup2(fds[i - 1][READ], STDIN_FILENO) == -1)
		ft_error(DUP, NULL);
	close(fds[i - 1][READ]);
	if (dup2(fds[i][WRITE], STDOUT_FILENO) == -1)
		ft_error(DUP, NULL);
	close(fds[i][WRITE]);
	if (execve(arguments.commands[i], arguments.splits[i], env) == -1)
		ft_error(COMMAND, arguments.argv[i + 2]);
}


int	main(int argn, char **argv, char **env)
{
	t_arguments_bonus	arguments;
	pid_t				*pid;
	int					**fds;
	int					i;

	arguments = check_arg_bonus(argn, argv, env);
	fds = ft_calloc(argn - 3 - arguments.here_doc - 1, sizeof(int*));
	pid = ft_calloc(argn - 3 - arguments.here_doc, sizeof(pid_t));

	if (!fds || !pid)
    {
        ft_error(MALLOC, NULL);
    }

	i = -1;
	while (++i < argn - 3 - arguments.here_doc - 1)
	{
		fds[i] = ft_calloc(2, sizeof(int));
		if (!fds[i])
        {
            while (i > 0)
                free(fds[--i]);
            free(fds);
            free(pid);
            ft_error(MALLOC, NULL);
        }
		if (pipe(fds[i]) == -1)
		{
			while (i > 0)
				free(fds[--i]);
			free(fds);
			ft_error(PIPE, NULL);
		}
	}
	i = -1;
	while (++i < argn - 3 - arguments.here_doc)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			ft_error(FORK, NULL);
		if (pid[i] == 0)
        {
            if (i == 0)
                child_first(arguments, fds[0], env);
            else if (i == argn - 3 - arguments.here_doc - 1)
                child_last(arguments, fds, env, argn);
            else
                exec_commands(arguments, fds, env, i);
            exit(0);
        }
	}
	i = -1;
	while (++i < argn - 3 - arguments.here_doc - 1)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		free(fds[i]);
	}
	i = -1;
	while (++i < argn - 3 - arguments.here_doc)
	{
		if (waitpid(pid[i], NULL, 0) == -1)
			ft_error(WAIT, NULL);
	}
	// Imprimir la estructura	
	//print_arguments_bonus(&arguments);

	free(fds);
	free(pid);


	// Liberar la memoria de la estructura
	free_arguments_bonus(&arguments);
	exit(0);
	return (0);
}
