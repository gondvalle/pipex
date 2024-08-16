/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-val <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:27:47 by gdel-val          #+#    #+#             */
/*   Updated: 2024/04/23 19:27:58 by gdel-val         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

size_t	where_path(char **env)
{
	size_t	i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		i++;
	return (i);
}

char	**ft_free(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		mat[i] = NULL;
		i++;
	}
	free(mat);
	mat = NULL;
	return (NULL);
}

void	ft_error(char *str, char *file)
{
	char	*msg;

	msg = ft_strjoin(str, file);
	if (!msg)
		return (perror("Error\n"));
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
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

char	*ft_threejoin(char const *s1, char const *s2, char const *s3)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		ft_error(MALLOC, NULL);
	str = ft_strjoin(tmp, s3);
	if (!str)
	{
		free(tmp);
		ft_error(MALLOC, NULL);
	}
	free(tmp);
	return (str);
}

// Función para imprimir el contenido de la estructura
void print_arguments_bonus(t_arguments_bonus *args)
{
    // Imprimir los enteros
    printf("in_fd: %d\n", args->in_fd);
    printf("out_fd: %d\n", args->out_fd);
    printf("here_doc: %d\n", args->here_doc);

    // Imprimir los comandos
    if (args->commands != NULL)
    {
        printf("commands:\n");
        for (int i = 0; args->commands[i] != NULL; i++)
        {
            printf("  commands[%d]: %s\n", i, args->commands[i]);
        }
    }

	// Imprimir los comandos
    if (args->argv != NULL)
    {
        printf("argv:\n");
        for (int i = 0; args->argv[i] != NULL; i++)
        {
            printf("  argv[%d]: %s\n", i, args->argv[i]);
        }
    }

    // Imprimir los splits
    if (args->splits != NULL)
    {
        printf("splits:\n");
        for (int i = 0; args->splits[i] != NULL; i++)
        {
            printf("  splits[%d]:\n", i);
            for (int j = 0; args->splits[i][j] != NULL; j++)
            {
                printf("    splits[%d][%d]: %s\n", i, j, args->splits[i][j]);
            }
        }
    }
}

// Función para liberar la memoria de la estructura
void free_arguments_bonus(t_arguments_bonus *args)
{
    // Liberar los comandos
    if (args->commands != NULL)
    {
        for (int i = 0; args->commands[i] != NULL; i++)
        {
            free(args->commands[i]);
        }
        free(args->commands);
    }

    // Liberar los splits
    if (args->splits != NULL)
    {
        for (int i = 0; args->splits[i] != NULL; i++)
        {
            for (int j = 0; args->splits[i][j] != NULL; j++)
            {
                free(args->splits[i][j]);
            }
            free(args->splits[i]);
        }
        free(args->splits);
    }
}