/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:05:04 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/16 10:48:34 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

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
		ft_printf("%d %s\n", count, line);
		count++;
		free(line);
		line = get_next_line(fd, core);
		if (!line && core->error == 1)
			return (free(line), close(fd), -1);
		/*
		if (ft_strncmp(line, "NO", 3) == 0)
			core->North = line;
		if (ft_strncmp(line, "SO", 3) == 0)
			core->South = line;
		if (ft_strncmp(line, "WE", 3) == 0)
			core->West = line;
		if (ft_strncmp(line, "EA", 3) == 0)
			core->East = line; */
	}
	close(fd);
	return (count);
}

int main(int argc, char **argv)
{
	t_data core;

	ft_bzero(&core, sizeof(core));
	if (argc != 2)
	{
		write(2, "Not the correct amount of arguments\n", 37);
		//write(2, "Error\n", 37);
		return (-1);
	}
	if (GetData(argv[1], &core) == -1)
		return (-1);

	ft_printf("North: %s\n", core.North);
	ft_printf("South: %s\n", core.South);
	ft_printf("East: %s\n", core.East);
	ft_printf("West: %s\n", core.West);
}