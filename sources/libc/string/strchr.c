/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:57:53 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:57:55 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*__strchr(char *__s, int __c)
{
	int	i;

	i = 0;
	while (__s[i])
	{
		if (__s[i] == __c)
			return (&__s[i]);
		++i;
	}
	if (__s[i] == __c)
		return (&__s[i]);
	return (NULL);
}

char	*__strstr(char *string, char *substring)
{
	char	*a;
	char	*b;

	b = substring;
	if (*b == 0)
		return (string);
	while (*string)
	{
		if (*string == *b)
		{
			a = string;
			while (*b && *a && *b == *a)
			{
				a++;
				b++;
			}
			if (*b == 0)
				return (string);
			b = substring;
		}
		string++;
	}
	return (NULL);
}

char	*__strrep(char *base, char *oldw, char *neww)
{
	size_t	oldwlen;
	size_t	newwlen;
	size_t	len;
	char	*rep;
	char	*occ;

	occ = __strstr(base, oldw);
	oldwlen = __strlen(oldw);
	newwlen = __strlen(neww);
	len = __strlen(base) - oldwlen + newwlen;
	rep = allocate(len + 1);
	__memcpy(rep, base, occ - base);
	if (*neww)
		__memcpy(rep + (occ - base), neww, newwlen);
	__memcpy(rep + (occ - base) + newwlen, occ + oldwlen,
		__strlen(occ + oldwlen));
	return (rep);
}
