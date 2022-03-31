/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:58:12 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:58:14 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*__strjoin(char *s1, char	*s2)
{
	char	*join;
	char	*ptr;

	join = allocate(((__strlen(s1) + __strlen(s2) + 1)));
	if (!join)
		return (NULL);
	ptr = join;
	if (s1)
	{
		while (*s1)
		{
			*join++ = *s1++;
		}
	}
	if (s2)
		while (*s2)
			*join++ = *s2++;
	*join = '\0';
	return (ptr);
}

char	*__strndup(char *s, size_t n)
{
	char	*new;
	size_t	len;

	len = __strnlen(s, n);
	new = (char *)allocate(len + 1);
	if (new == NULL)
		return (NULL);
	new[len] = '\0';
	return ((char *)__memcpy(new, s, len));
}

char	*__strdup(char *s)
{
	size_t	len;
	void	*new;

	len = __strlen(s) + 1;
	new = allocate(len);
	return ((char *) __memcpy (new, s, len));
}

char	*__strncpy(char *__dest, char *__src, size_t __n)
{
	size_t	i;

	i = 0;
	while (i < __n && *__src)
	{
		*__dest = *__src;
		++__dest;
		++__src;
	}
	return (__dest);
}

char	*__strcpy(char *__dest, char *__src)
{
	while (*__src)
	{
		*__dest = *__src;
		++__dest;
		++__src;
	}
	return (__dest);
}
