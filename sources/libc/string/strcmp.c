/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:58:02 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:58:04 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*ft_strcat(char *dst, const char *src)
{
	char	*anchor;

	anchor = dst;
	while (*dst)
		++dst;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (anchor);
}

int	__strcmp(char *p1, char *p2)
{
	if (!p1 || !p2)
		return (-1);
	while (*p1 && *p2 && *p1 == *p2)
	{
		++p1;
		++p2;
	}
	return ((unsigned char)(*p1) - (unsigned char)(*p2));
}
