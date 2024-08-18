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

void	ft_error(char *str, char *file)
{
	char	*msg;

	if (file)
	{
		msg = ft_strjoin(str, file);
		if (!msg)
			return (perror("Error\n"));
		ft_putstr_fd(msg, 2);
	}
	else
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

size_t	where_path(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	ft_error(ENV, NULL);
	return (0);
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
