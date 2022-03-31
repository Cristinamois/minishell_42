/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:58:19 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:58:21 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

size_t	__strnlen(char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen)
	{
		if (!*s)
			break ;
		++s;
		++len;
	}
	return (len);
}

size_t	__strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		++i;
	return (i);
}

void	__putnstr(char *str, size_t n)
{
	if (str)
		write(STDOUT_FILENO, str, n);
}

void	__putstr_fd(char *str, int fd)
{
	write(fd, str, __strlen(str));
}
