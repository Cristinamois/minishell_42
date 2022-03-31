/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:59:53 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:59:57 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	environment_patch(t_token *head)
{
	char	*value;

	while (head)
	{
		if (head->type != ETT_SQWORD && head->type != ETT_SPACE)
		{
			value = __strdup(head->value);
			while (*value)
			{
				if (*value == '$')
					value = on_dollar(head, value);
				else
					++value;
			}
		}
		head = head->next;
	}
}

static void	sighandler(int signo)
{
	if (signo == SIGINT)
	{
		g_memory.status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_memory.active)
			rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		__putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	}
}

void	redirect_signals(void)
{
	sig_t	ret;

	ret = signal(SIGQUIT, &sighandler);
	if (ret == SIG_ERR)
		throw_("unable to redirect SIGQUIT", true, 0);
	ret = signal(SIGINT, &sighandler);
	if (ret == SIG_ERR)
		throw_("unable to redirect SIGINT", true, 0);
}

void	quit(t_allocation *allocated, int status, bool nexit)
{
	t_allocation	*previous;

	g_memory.status = status;
	while (allocated)
	{
		if (allocated->value)
		{
			free(allocated->value);
			allocated->value = NULL;
		}
		previous = allocated;
		allocated = allocated->next;
		free(previous);
		previous = NULL;
	}
	if (g_memory.cwd)
		free(g_memory.cwd);
	if (nexit)
		exit(status);
}

void	throw_(char *errstr, bool prefix, int code)
{
	if (prefix)
		printf("minishell: ");
	printf("%s\n", errstr);
	quit(g_memory.allocated, code, true);
}
