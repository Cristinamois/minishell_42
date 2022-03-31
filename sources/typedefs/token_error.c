/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:59:03 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:59:05 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ett_error_previous(t_token *previous)
{
	if (!previous)
		throw_("syntax error near unexpected token `|'", true, 2);
	if (__toktype(previous) != ETT_WORD)
	{
		printf("minishell: ");
		printf("syntax error near unexpected token `%s'\n", previous->value);
		quit(g_memory.allocated, 2, true);
	}
}

void	ett_error_next(t_token *next)
{
	if (!next)
		throw_("syntax error near unexpected token `newline'", true, 2);
	if (__toktype(next) != ETT_WORD && !next->next)
	{
		printf("minashell: ");
		printf("syntax error near unexpected token `%s'\n", next->value);
		quit(g_memory.allocated, 2, true);
	}
}

void	ett_dollar_token(char **new, t_token *next, char *anchor)
{
	t_variable	*var;

	*new = __strndup(next->value, anchor - next->value - 1);
	var = search_environment(*new + 1);
	if (!var)
	{
		printf("minishell: %s: ambiguous redirect\n", *new);
		quit(g_memory.allocated, 1, true);
	}
}

void	check_token(t_token *token, int mode, t_token *previous)
{
	t_token			*next;
	char			*anchor;
	int				len;
	char			*new;

	if (!mode)
	{
		next = token->next;
		ett_error_next(next);
		anchor = next->value;
		if (*anchor == '$')
		{
			len = 1;
			while (anchor[len] && !__isspace(anchor[len])
				&& !__issupported(anchor[len]) && anchor[len] != '$'
				&& anchor[len] != '/')
				++len;
			if (len != 1)
				ett_dollar_token(&new, next, anchor);
		}
		return ;
	}
	ett_error_previous(previous);
}

void	fork_check_syntax_err(t_token *head)
{
	t_token	*previous;

	previous = NULL;
	while (head)
	{
		if (__toktype(head) == ETT_REDIRECT)
			check_token(head, 0, NULL);
		if (head->type == ETT_PIPE)
			check_token(head, 1, previous);
		previous = head;
		head = head->next;
	}
	quit(g_memory.allocated, 0, true);
}
