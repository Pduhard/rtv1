/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/30 20:56:52 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/21 03:37:49 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

void	loop_manage_cam(t_data *data)
{

	if (data->hooks & (ARR_LEFT_KEY | ARR_RIGHT_KEY))
	{
		if (data->hooks & ARR_LEFT_KEY)
			data->camera->rotation.val[1] -= 3;
		if (data->hooks & ARR_RIGHT_KEY)
			data->camera->rotation.val[1] += 3;
			data->rot_mat[1] = init_rotation_matrix_y(degree_to_radian(data->camera->rotation.val[1]));
	}
	if (data->hooks & (ARR_UP_KEY | ARR_DOWN_KEY))
	{
		if (data->hooks & ARR_UP_KEY && data->camera->rotation.val[0] < 90)
			data->camera->rotation.val[0] += 3;
		if (data->hooks & ARR_DOWN_KEY && data->camera->rotation.val[0] > -90)
			data->camera->rotation.val[0] -= 3;
	}
	if (data->hooks & (W_KEY | S_KEY))
	{
		t_3vecf dir = mult_3vecf_33matf(assign_3vecf(0, 0, 0.2), data->rot_mat[1]);
		if (data->hooks & W_KEY)
		{
			data->camera->origin.val[0] += dir.val[0];
			data->camera->origin.val[1] += dir.val[1];
			data->camera->origin.val[2] += dir.val[2];
		}
		if (data->hooks & S_KEY)
		{
			data->camera->origin.val[0] -= dir.val[0];
			data->camera->origin.val[1] -= dir.val[1];
			data->camera->origin.val[2] -= dir.val[2];
		}
	}
	if (data->hooks & (A_KEY | D_KEY))
	{
		t_3vecf dir = mult_3vecf_33matf(assign_3vecf(0.2, 0, 0), data->rot_mat[1]);
		if (data->hooks & A_KEY)
		{
			data->camera->origin.val[0] -= dir.val[0];
			data->camera->origin.val[1] -= dir.val[1];
			data->camera->origin.val[2] -= dir.val[2];
		}
		if (data->hooks & D_KEY)
		{
			data->camera->origin.val[0] += dir.val[0];
			data->camera->origin.val[1] += dir.val[1];
			data->camera->origin.val[2] += dir.val[2];
		}
	}
		if (data->hooks & SPACE_KEY)
			data->camera->origin.val[1] -= 0.2;
		if (data->hooks & SHIFT_KEY)
			data->camera->origin.val[1] += 0.2;
}

int		print_loop_image(void *param)
{
	t_data *data;
	data = (t_data *)param;

	loop_manage_cam(data);
	mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img_ptr);
	data->mlx->img_ptr = mlx_new_image(data->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->mlx->img_str = (int *)mlx_get_data_addr(data->mlx->img_ptr,
			&(data->mlx->bpp), &(data->mlx->s_l), &(data->mlx->endian));
	render(data);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->mlx->img_ptr, 0, 0);
	return (1);
}
