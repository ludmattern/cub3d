/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:14:40 by fprevot           #+#    #+#             */
/*   Updated: 2024/05/21 16:58:29 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>

# define ERROR		0
# define SUCCESS	1
# define ERR		"Error\n"
# define ALLOC_ERR	"Failed to allocate memory"

/* parsing structures */
typedef struct s_position
{
	int			row;
	int			col;
}				t_pos;

typedef struct s_texture_map
{
	const char	*prefix;
	char		**texture;
}				t_texture_map;

typedef struct s_color_map
{
	const char	*prefix;
	int			*color;
}				t_color_map;

typedef struct s_map
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

/* execution structures */
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_ppixel;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_data_img
{
	void	*img;
	char	*addr;
	int		bits_ppixel;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_data_img;

typedef struct s_scene_ctx
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		draw_start;
	int		draw_end;
	int		wall_color;
	int		line_height;
	int		text_num;
	double	wall_x;
	int		text_x;
	int		texture_y;
	int		ceiling_color;
	int		floor_color;
}	t_scene_ctx;

typedef struct s_ray
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			move_forward;
	int			move_backward;
	int			move_right;
	int			move_left;
	int			cam_right;
	int			cam_left;
	int			ceiling_color;
	int			floor_color;
	t_cub		*cub;
	t_map		*map;
	t_texture	texture[4];
}	t_ray;

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

/* execution */
void	start_exec(t_cub *cub);

/* raycasting */
int		update_frame(t_ray *rc);
void	calc_wall_dimensions(t_scene_ctx *ctx, t_ray *rc);
void	draw_scene(t_ray *rc, int x);
void	draw_line(t_scene_ctx *ctx, t_ray *rc, int x, t_data_img *img);
t_ray	*init_raycasting(t_cub *cub);

/* key handling */
int		handle_keyrelease(int keycode, t_ray *rc);
int		handle_keypress(int keycode, t_ray *rc);

/* freeing memory */
int		clean_exit(t_cub *cub, int exit_code);
int		clean_return(char *line, char **lines, int status);
void	free_all(t_ray *rc);
int		handle_img_err(t_ray *rc);

#endif	