/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:07:45 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/23 12:55:20 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	extracting_link(char **core)
{
	char *str;
	char *temp;
	str = NULL;
	str = ft_strchr(*core, ' ');
	if (str != NULL)
		str++;
	temp = ft_strdup(str);
	free(*core);
	*core = ft_strdup(temp);
	free(temp);
}

void	valid_file_checker(char *str, t_data *core)
{
	int fd;
	fd = 0;

	fd = open(str, O_RDONLY);
	if (fd == -1) //Note that this should free the elements
		error_exit(core, "Error\nInvalid Texture Files!\n");
}

void	AllLinkExtractor(t_data *core)
{
	if (!core->North || !core->East || !core->South || !core->West)
		error_exit(core, "Error\nEmpty Textures!\n");
	extracting_link(&core->North);
	core->North[ft_strlen(core->North) - 1] = '\0';
	valid_file_checker(core->North, core);
	extracting_link(&core->South);
	core->South[ft_strlen(core->South) - 1] = '\0';
	valid_file_checker(core->South, core);
	extracting_link(&core->East);
	core->East[ft_strlen(core->East) - 1] = '\0';
	valid_file_checker(core->East, core);
	extracting_link(&core->West);
	core->West[ft_strlen(core->West) - 1] = '\0';
	valid_file_checker(core->West, core);
}
