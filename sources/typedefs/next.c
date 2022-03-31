/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:58:50 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:58:52 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	*get_last_next(void *head)
{
	t_next	*hd;

	hd = (t_next *)head;
	if (!hd)
		return (head);
	while (hd->next)
		hd = hd->next;
	return ((void *)hd);
}

void	add_next(void **head, void *value)
{
	t_next	*last;
	t_next	**hd;

	hd = (t_next **)head;
	if (!*hd)
	{
		*hd = (t_next *)value;
		return ;
	}
	last = get_last_next(*hd);
	last->next = (t_next *)value;
}

size_t	get_next_size(void *head)
{
	t_next	*c;
	size_t	size;

	c = (t_next *)head;
	size = 0;
	while (c)
	{
		++size;
		c = c->next;
	}
	return (size);
}
