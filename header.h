/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:57:24 by aruckenb          #+#    #+#             */
/*   Updated: 2025/05/22 09:50:26 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"

/*Buffer for get next_line*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

//So_Long Functions but also math.h
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"

typedef struct s_data
{
	char	**map;		//Full Map
	int		top;
	int		bottom; //This contains the rbg for the ceiling and floor

	//These char contain the file path for the images
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	
	int	px;
	int	py;
	char	direction;
	
	int		error;
	int checker;

} t_data;

typedef struct s_game
{
	int			px;
	int			py;
	int			pdir;
	
	void		*mlx_ptr;
	void		*win_ptr;
		
	void		*img_N;
	void		*img_S;
	void		*img_W;
	void		*img_E;
	
	void		*img_C;
	void		*img_F;
	
} t_game;

/*Parsing && Map Functions*/
int		getdata(char *file, t_data *core, unsigned int	count);
char	**get_map_char_len(int map_size, char *str, t_data *vars);
void	alllinkextractor(t_data *core);
void	map_checker(t_data *core);


/*Get_Next_Line*/
char	*get_next_line(int fd, t_data *vars);
size_t	ft_strlen1(const char *str);
char	*ft_strchr1(const char *str, int c);
char	*ft_strjoin1(char const *s1, char const *s2);
char	*ft_strdup1(const char *src);

/*Utils Function*/
void	free_array(char **example);
char	*ft_strcpy(char *dest, char *src);
void	map_error(int fd, char *str);
void	error_exit(t_data *core, const char *msg);
int		ft_atoi1(const char *nptr);

#endif