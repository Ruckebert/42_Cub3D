/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:17:58 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/23 12:56:37 by aruckenb         ###   ########.fr       */
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


void error_exit(t_data *core, const char *msg) 
{
	if (core->Map)
		free_array(core->Map);
	if (core->North)
		free(core->North);
	if (core->South)
		free(core->South);
	if (core->East)
		free(core->East);
	if (core->West)
		free(core->West);
	write(2, msg, ft_strlen(msg));
    exit(2);
}

void	map_error(int fd, char *str)
{
	close(fd);
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	exit(2);
}