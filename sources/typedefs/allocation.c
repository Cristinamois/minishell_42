/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:58:45 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:58:46 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	*allocate(size_t size)
{
	t_allocation	*allocation;

	allocation = malloc(sizeof(t_allocation));
	if (!allocation)
		throw_("unable to allocate enough memory", true, 0);
	allocation->next = NULL;
	allocation->value = malloc(size);
	if (!allocation->value)
		throw_("unable to allocate enough memory", true, 0);
	__memset(allocation->value, 0x00, size);
	add_next((void **)&g_memory.allocated, (void *)allocation);
	return (allocation->value);
}
