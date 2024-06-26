/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-val <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:12:13 by gdel-val          #+#    #+#             */
/*   Updated: 2023/09/14 00:15:09 by gdel-val         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9'))
	{
		return (1);
	}
	return (0);
}
