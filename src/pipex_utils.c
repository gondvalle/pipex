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

char	*ft_threejoin(char const *s1, char const *s2, char const *s3)
{
	char	*tmp;
	char	*str;
		
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		ft_error(MALLOC, NULL);
	str = ft_strjoin(tmp, s3);
	if (!str)
		ft_error(MALLOC, NULL);
	free(tmp);
	return (str);
}

void ft_error(char *str, char *file)
{
	char	*msg;

	msg = ft_strjoin(str, file);
	if (!msg)
		return (perror("Error\n"));
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}
