/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:00:43 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 15:00:48 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*on_word(char *word)
{
	size_t	len;

	len = 0;
	while (word[len] && !__isspace(word[len]) && !__issupported(word[len]))
		++len;
	add_token(ETT_WORD, word, len);
	return (&word[len]);
}

char	*on_redirect(char *redirect)
{
	if (*redirect == '<' && *(redirect + 1) == '<')
	{
		add_token(ETT_DRINPUT, redirect, 2);
		return (redirect + 2);
	}
	else if (*redirect == '>' && *(redirect + 1) == '>')
	{
		add_token(ETT_DROUTPUT, redirect, 2);
		return (redirect + 2);
	}
	else if (*redirect == '<')
	{
		add_token(ETT_SRINPUT, redirect, 1);
		return (redirect + 1);
	}
	else
	{
		add_token(ETT_SROUTPUT, redirect, 1);
		return (redirect + 1);
	}
}

char	*on_qword(char *fquote)
{
	char	*squote;

	squote = __strchr(fquote + 1, *fquote);
	if (!squote)
	{
		squote = __strchr(fquote, '\x00');
		printf("minishell: ");
		printf("syntax error near unexpected token `newline'\n");
		g_memory.flag = 1;
	}
	add_token(*fquote, fquote + 1, squote - fquote - 1);
	if (*squote)
		++squote;
	return (squote);
}

void	tokenize(char *cmd)
{
	g_memory.tokens = NULL;
	g_memory.flag = 0;
	while (*cmd)
	{
		if (__isspace(*cmd))
		{
			add_token(ETT_SPACE, cmd, 1);
			while (*cmd && __isspace(*cmd))
				++cmd;
		}
		else if (*cmd == '\'' || *cmd == '\"')
			cmd = on_qword(cmd);
		else if (*cmd == '<' || *cmd == '>')
			cmd = on_redirect(cmd);
		else if (*cmd == '|')
		{
			add_token(ETT_PIPE, cmd, 1);
			++cmd;
		}
		else
			cmd = on_word(cmd);
	}
	update_token();
}
