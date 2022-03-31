/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:59:15 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:59:16 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*on_dollar(t_token *token, char *dollar)
{
	size_t		len;
	char		*key;
	t_variable	*variable;

	len = 1;
	while (dollar[len] && !__isspace(dollar[len]) && !__issupported(dollar[len])
		&& dollar[len] != '$' && dollar[len] != '/' && (dollar[len] == '_'
			|| isalnum(dollar[len]) || dollar[len] == '?'))
		++len;
	key = __strndup(dollar, len);
	variable = search_environment(key + 1);
	if (!__strcmp(key, "$?"))
		token->value = __strrep(token->value, key, __itoa(g_memory.status));
	else if ((!variable && len >= 1) || (len == 1 && token->next
			&& __toktype(token->next) == ETT_WORD))
		token->value = __strrep(token->value, key, "");
	else if (variable)
		token->value = __strrep(token->value, key, variable->value);
	return (dollar + len);
}

t_variable	*search_environment(char *key)
{
	t_variable	*environment;

	environment = g_memory.environment;
	while (environment)
	{
		if (!__strcmp(environment->key, key))
			return (environment);
		environment = environment->next;
	}
	return (NULL);
}

void	show_environment(t_variable *environment)
{
	while (environment)
	{
		printf("%s=%s\n", environment->key, environment->value);
		environment = environment->next;
	}
}

void	export_variable(char *key, size_t keylen, char *value)
{
	t_variable	*variable;

	variable = allocate(sizeof(t_variable));
	variable->next = NULL;
	variable->key = __strndup(key, keylen);
	variable->value = __strdup(value);
	add_next((void **)&g_memory.environment, variable);
}

void	build_environment(char **ep)
{
	size_t	i;
	char	*equal;

	i = 0;
	while (ep[i])
	{
		equal = __strchr(ep[i], '=');
		export_variable(ep[i], equal - ep[i], equal + 1);
		++i;
	}
	if (!search_environment("PATH"))
		export_variable("PATH", 4, \
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	g_memory.cwd = getcwd(NULL, 0);
	if (!g_memory.cwd)
		throw_("unable to getcwd", true, 0);
	if (!search_environment("PWD"))
		export_variable("PWD", 3, g_memory.cwd);
	if (!search_environment("OLDPWD"))
		export_variable("OLDPWD", 6, g_memory.cwd);
}
