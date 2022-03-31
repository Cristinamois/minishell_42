/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:58:33 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:58:34 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int	word_size(char const *str, char charset)
{
	int		size;

	size = 0;
	while (*str && !(*str == charset))
	{
		++size;
		++str;
	}
	return (size);
}

static int	ft_words_count(char const *str, char charset, char ***ret)
{
	int		words;
	int		state;

	state = true;
	words = 0;
	while (*str)
	{
		if (*str == charset)
			state = true;
		else
		{
			if (state)
				++words;
			state = false;
		}
		++str;
	}
	*ret = (char **)allocate(sizeof(char *) * (words + 1));
	return (words);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	int		index;
	int		i;
	char	**ret;

	if (!s)
		return (0);
	words = ft_words_count(s, c, &ret);
	if (!ret)
		return (0);
	index = -1;
	while (++index < words)
	{
		while (*s && *s == c)
			++s;
		ret[index] = (char *)allocate(sizeof(char) * (word_size(s, c) + 1));
		i = 0;
		while (*s && !(*s == c))
			ret[index][i++] = *s++;
		ret[index][i] = 0;
	}
	ret[words] = 0;
	return (ret);
}
