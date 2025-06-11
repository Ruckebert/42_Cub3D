/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:17:37 by aruckenb          #+#    #+#             */
/*   Updated: 2025/06/11 11:37:57 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	rgbloop(char *line, int i, int *type)
{
	*type = ft_atoi1(&line[i]);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] != ',')
		return (-1);
	i++;
	return (i);
}

int	rgbfirst(char *line, int i)
{
	while (line[i] && !ft_isdigit(line[i]))
	{
		if (line[i] != ' ')
			return (free(line), -1);
		i++;
	}
	return (i);
}
