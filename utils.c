/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:17:58 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/16 14:19:31 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_array(char **example)
{
	int	i;

	i = 0;
	if (example)
	{
		while (example[i])
		{
			free(example[i]);
			i++;
		}
		free(example);
	}
}

char	*ft_strcpy(char *dest, char *src)
{
	char	*start;

	start = dest;
	while (*src != '\0')
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest = *src;
	return (start);
}

void	map_error(int fd, char *str)
{
	close(fd);
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	exit(2);
}