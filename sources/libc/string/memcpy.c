/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:57:45 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:57:47 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	__sortarr(char **arr)
{
	char	*tmp;
	int		i;
	int		k;

	if (!arr || !*arr)
		return ;
	i = -1;
	while (arr[++i])
	{
		k = i;
		while (k && __strcmp(arr[k], arr[k - 1]) < 0)
		{
			tmp = arr[k];
			arr[k] = arr[k - 1];
			arr[k - 1] = tmp;
			k--;
		}
	}
}

void	*__memcpy(void *dest, void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	while (len--)
		*d++ = *s++;
	return (dest);
}

void	*__memset(void *dest, int val, size_t len)
{
	unsigned char	*ptr;

	ptr = dest;
	while (len-- > 0)
		*ptr++ = val;
	return (dest);
}
