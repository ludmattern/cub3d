/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:14:40 by fprevot           #+#    #+#             */
/*   Updated: 2024/05/20 16:05:41 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>

# define ERROR		0
# define SUCCESS	1
# define ERR		"Error\n"
# define ALLOC_ERR	"Failed to allocate memory"

typedef struct	s_position
{
	int			row;
	int			col;
}				t_pos;

typedef struct	s_texture_map
{
	const char	*prefix;
	char		**texture;
}				t_texture_map;

typedef struct	s_color_map
{
	const char	*prefix;
	int			*color;
}				t_color_map;

typedef struct	s_map
{
	int			**grid;
	size_t		width;
	size_t		height;
}				t_map;

typedef struct s_player
{
	int			x;
	int			y;
	char		heading;
}				t_player;

typedef struct s_styles
{
	int			floor;
	int			ceiling;
}				t_styles;

typedef struct s_textures
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
}				t_textures;

typedef struct s_cub
{
	int			filefd;
	t_map		map;
	t_player	player;
	t_styles	styles;
	t_textures	textures;
}				t_cub;

/* initialisation and first checks */
int		check_program_args(int argc, char **argv);
int		check_submitted_file(char *file, int *filefd);
t_cub	*init_cub_data_struct(void);

/* general parsing */
int		parse_parameters(t_cub *cub);

/* texture parsing */
int		process_texture(t_cub *cub, char *line);

/* color parsing */
int		process_style(t_cub *cub, char *line);
void	init_color_map(t_color_map *color_map, t_cub *cub);
int		check_color_input(char *color);
int		check_comma(char *str, const char *line);
int		validate_rgb_range(int *value, const char *str);

/* map parsing */
int		parse_lines(t_cub *cub, char **lines);
int		extract_map_lines(t_cub *cub, char **line, char ***lines);
int		skip_empty_lines(int fd, char **line);
int		check_end_of_file(int fd, char **line);
int		check_map_validity(t_map *map);

/* freeing memory */
int		clean_exit(t_cub *cub, int exit_code);
int		clean_return(char *line, char **lines, int status);

#endif	