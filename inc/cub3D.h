/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cub3D.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: fprevot <fprevot@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/19 17:14:40 by fprevot		   #+#	#+#			 */
/*   Updated: 2024/05/17 18:10:10 by fprevot		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_map
{
	int	width;
	int	height;
	int	**map;
}	t_map;

typedef struct s_data_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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
	int		ceiling_color;
	int		floor_color;
	int		line_height;
	int		texture_num;
	double	wall_x;
	int		texture_x;
	int		texture_y;
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
	t_map		*map;
	t_texture	textures[4];
}	t_ray;

void	start_exec(void);
void	draw_scene(t_ray *rc, int x);
int		handle_keyrelease(int keycode, t_ray *rc);
int		update_frame(t_ray *rc);
int		handle_keypress(int keycode, t_ray *rc);
void	free_all(t_ray *rc);
void	calc_wall_dimensions(t_scene_ctx *ctx, t_ray *rc);

void free_map(t_map *map);

#endif
