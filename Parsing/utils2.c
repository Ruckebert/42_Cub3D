/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:17:37 by aruckenb          #+#    #+#             */
/*   Updated: 2025/06/18 16:21:29 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	rgbloop(char *line, long long i, int *type)
{
	int	count;

	count = 0;
	*type = ft_atoi1(&line[i]);
	while (line[i] && ft_isdigit(line[i]))
	{
		i++;
		count++;
		if (count > 3)
			return (free(line), -1);
	}
	if (line[i] != ',')
		return (free(line), -1);
	i++;
	return (i);
}

int	rgbfirst(char *line, long long i)
{
	while (line[i] && !ft_isdigit(line[i]))
	{
		if (line[i] != ' ')
			return (free(line), -1);
		i++;
	}
	return (i);
}
