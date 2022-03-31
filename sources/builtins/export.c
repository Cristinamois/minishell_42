/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:57:11 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:57:12 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**export_env(t_variable *env)
{
	char	**ret;
	size_t	size;
	size_t	i;

	size = get_next_size(env);
	ret = allocate(sizeof(char *) * (size + 1));
	ret[size] = NULL;
	i = 0;
	while (i < size)
	{
		ret[i] = allocate(__strlen(env->key) + __strlen(env->value) + 2);
		ret[i] = ft_strcat(ret[i], env->key);
		ret[i] = ft_strcat(ret[i], "=");
		ret[i] = ft_strcat(ret[i], env->value);
		env = env->next;
		++i;
	}
	return (ret);
}

bool	exec_env(void)
{
	t_variable	*head;

	head = g_memory.environment;
	while (head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return (true);
}

void	overwrite_var(char *key, char *newvalue)
{
	t_variable	*var;

	var = search_environment(key);
	if (!var)
		return ;
	var->value = __strdup(newvalue);
}

void	exec_export(int ac, char **av)
{
	int		i;
	char	*eq;
	char	*id;

	i = 0;
	while (++i < ac)
	{
		eq = __strchr(av[i], '=');
		if (!eq)
		{
			if (!is_valid_id(av[i]))
				export_error(av[i]);
			continue ;
		}
		id = __strndup(av[i], eq - av[i]);
		if (!is_valid_id(id))
		{
			export_error(av[i]);
			continue ;
		}
		if (!search_environment(id))
			export_variable(id, __strlen(id), eq + 1);
		else
			overwrite_var(id, eq + 1);
	}
}

void	__export_external(void)
{
	char	**ep;
	int		i;
	char	*eq;

	ep = export_env(g_memory.environment);
	__sortarr(ep);
	i = -1;
	while (ep[++i])
	{
		__putstr_fd("export ", STDOUT_FILENO);
		eq = __strchr(ep[i], '=');
		__putnstr(ep[i], eq - ep[i]);
		__putstr_fd("=\"", STDOUT_FILENO);
		__putstr_fd(eq + 1, STDOUT_FILENO);
		__putstr_fd("\"\n", STDOUT_FILENO);
	}
}
