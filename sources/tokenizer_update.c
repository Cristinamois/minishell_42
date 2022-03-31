/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:00:31 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 15:00:33 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	space_token_suppresser(void)
{
	t_token	*previous;
	t_token	*head;

	head = g_memory.tokens;
	previous = NULL;
	while (head)
	{
		if (head->type == ETT_SPACE)
		{
			if (previous)
				previous->next = head->next;
			else
				g_memory.tokens = head->next;
		}
		previous = head;
		head = head->next;
	}
}

void	link_tokens(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		if (next && __toktype(head) == ETT_WORD && __toktype(next) == ETT_WORD)
		{
			head->value = __strjoin(head->value, next->value);
			head->next = next->next;
		}
		else
			head = head->next;
	}
	space_token_suppresser();
}

void	update_token(void)
{
	link_tokens(g_memory.tokens);
	if (no_syntax_errors(g_memory.tokens) == 2)
	{
		g_memory.flag = 1;
		return ;
	}
	environment_patch(g_memory.tokens);
}
