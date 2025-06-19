/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:07:45 by aruckenb          #+#    #+#             */
/*   Updated: 2025/06/19 09:29:12 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	extracting_link(char **core)
{
	char	*str;
	char	*temp;
	int		i;

	i = 0;
	str = NULL;
	temp = NULL;
	str = *core;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		i -= 2;
	str = &str[i];
	temp = ft_strdup(str);
	free(*core);
	*core = temp;
}

void	valid_file_checker(char *str, t_data *core)
{
	int	fd;

	fd = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		error_exit(core, "Error\nInvalid Texture Files!\n");
	if (ft_strncmp(str + ft_strlen(str) - 4, ".xpm", 4) != 0)
		error_exit(core, "Error\nInvalid Texture Files!\n");
	close(fd);
}

void	alllinkextractor(t_data *core)
{
	if (core->checker != 15)
		error_exit(core, "Error\nDub Or No Textures!\n");
	if (!core->north || !core->east || !core->south || !core->west)
		error_exit(core, "Error\nEmpty Textures!\n");
	extracting_link(&core->north);
	core->north[ft_strlen(core->north) - 1] = '\0';
	valid_file_checker(core->north, core);
	extracting_link(&core->south);
	core->south[ft_strlen(core->south) - 1] = '\0';
	valid_file_checker(core->south, core);
	extracting_link(&core->east);
	core->east[ft_strlen(core->east) - 1] = '\0';
	valid_file_checker(core->east, core);
	extracting_link(&core->west);
	core->west[ft_strlen(core->west) - 1] = '\0';
	valid_file_checker(core->west, core);
}
