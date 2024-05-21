/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exec_start.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: fprevot <fprevot@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/20 16:03:07 by fprevot		   #+#	#+#			 */
/*   Updated: 2024/05/21 11:05:43 by fprevot		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function handles the keypress event received by the mlx loop and updates 
the raycasting structure accordingly.
*/
int	handle_keypress(int keycode, t_ray *rc)
{
	if (keycode == 65307)
	{
		mlx_loop_end(rc->mlx);
		return (0);
	}
	if (keycode == 119)
		rc->move_forward = 1;
	if (keycode == 115)
		rc->move_backward = 1;
	if (keycode == 100)
		rc->move_right = 1;
	if (keycode == 97)
		rc->move_left = 1;
	if (keycode == 65361)
		rc->cam_left = 1;
	if (keycode == 65363)
		rc->cam_right = 1;
	return (0);
}

/*
this function handles the keyrelease event received by the mlx loop and updates
the raycasting structure accordingly.
*/
int	handle_keyrelease(int keycode, t_ray *rc)
{
	if (keycode == 119)
		rc->move_forward = 0;
	if (keycode == 115)
		rc->move_backward = 0;
	if (keycode == 100)
		rc->move_right = 0;
	if (keycode == 97)
		rc->move_left = 0;
	if (keycode == 65361)
		rc->cam_left = 0;
	if (keycode == 65363)
		rc->cam_right = 0;
	return (0);
}

int	handle_destroy(t_ray *rc)
{
	mlx_loop_end(rc->mlx);
	return (0);
}

/*
this function starts the game loop and handles the keypress and keyrelease 
events.
*/
void	start_exec(t_cub *cub)
{
	t_ray	*rc;

	rc = init_raycasting(cub);
	if (rc == NULL)
		return ;
	mlx_hook(rc->win, 2, 1L << 0, handle_keypress, rc);
	mlx_hook(rc->win, 3, 1L << 1, handle_keyrelease, rc);
	mlx_loop_hook(rc->mlx, (int (*)(void *))update_frame, rc);
	mlx_hook(rc->win, 17, 0, handle_destroy, rc);
	mlx_loop(rc->mlx);
	free_all(rc);
}
