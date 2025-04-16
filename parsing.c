/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:12:04 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/16 11:12:32 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	map_invalid(int fd)
{
	close(fd);
	write(2, "Error\nInvalid File!\n", 21);
	exit(2);
}

void	file_empty(int fd)
{
	close(fd);
	write(2, "Error\nFile is empty!\n", 21);
	exit(2);
}

int GetData(char *file, t_data *core)
{
	int				fd;
	unsigned int	count;
	char	*line;
	
	line = NULL;
	count = 0;
	fd = open(file, O_RDWR);
	if (fd == -1)
		exit(write(2, "Error\nInvalid File!\n", 21));
	if (ft_strlen(file) < 5 || ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4)	!= 0 || ft_strncmp(file + ft_strlen(file) - 5, "/.cub", 5) == 0)
		map_invalid(fd);
	line = get_next_line(fd, core);
	if (!line)
		file_empty(fd);
	while (line)
	{
		//Copies North
		if (ft_strncmp(line, "NO", 2) == 0)
			core->North = ft_strdup(line);
		if (ft_strncmp(line, "SO", 2) == 0)
			core->South = ft_strdup(line);
		if (ft_strncmp(line, "WE", 2) == 0)
			core->West = ft_strdup(line);
		if (ft_strncmp(line, "EA", 2) == 0)
			core->East = ft_strdup(line);

			
		//ft_printf("%d %s\n", count, line);
		count++;
		free(line);
		line = get_next_line(fd, core);
		if (!line && core->error == 1)
			return (free(line), close(fd), -1);
	}
	close(fd);
	return (count);
}