/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:59:08 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:59:10 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	__issupported(int c)
{
	return (c == '\'' || c == '\"' || c == '<' || c == '>' || c == '|');
}

int	__toktype(t_token *token)
{
	t_token_type	type;

	type = token->type;
	if (type == ETT_SQWORD || type == ETT_DQWORD || type == ETT_WORD)
		return (ETT_WORD);
	else if (type == ETT_PIPE)
		return (ETT_REDIRECT);
	else if (type == ETT_SRINPUT || type == ETT_DRINPUT)
		return (ETT_REDIRECT);
	else if (type == ETT_SROUTPUT || type == ETT_DROUTPUT)
		return (ETT_REDIRECT);
	else
		return (ETT_NONE);
}

int	no_syntax_errors(t_token *head)
{
	pid_t			pid;
	int				status;

	pid = fork();
	if (pid == -1)
		throw_("unable to fork", true, 0);
	if (pid == 0)
		fork_check_syntax_err(head);
	wait(&status);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	return (status);
}

void	add_token(t_token_type type, char *value, size_t vallen)
{
	t_token	*token;

	token = allocate(sizeof(t_token));
	token->next = NULL;
	token->type = type;
	token->value = __strndup(value, vallen);
	add_next((void **)&g_memory.tokens, token);
}
