/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/30 20:56:52 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/30 22:56:40 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"
/*
void	loop_manage_speed(t_data *data)
{
	if (data->params.p_speed)
		data->speed += 0.01;
	else if (data->params.m_speed)
		data->speed -= 0.01;
	if (data->speed < 0.01)
		data->speed = 0.01;
	if (data->params.p_cam_speed)
		data->cam_speed += 0.1;
	else if (data->params.m_cam_speed)
		data->cam_speed -= 0.1;
	if (data->cam_speed < 0.1)
		data->cam_speed = 0.1;
}

void	loop_manage_render(t_data *data)
{
	if (get_magnitude(sub_points(data->cam.from, set_new_point(0, 0, 0)))
		< (data->line_size + data->line_nbr) / 2)
		data->fill = 0;
	data->fun_factor += data->params.fun_on ? 0.1 : -data->fun_factor + 1.0;
}
*/
void	loop_manage_cam(t_data *data)
{
	if (data->hooks & F_KEY)
	{
		data->camera->rotation.val[1] += 2;
		data->rot_mat[1] = init_rotation_matrix_y(degree_to_radian(data->camera->rotation.val[1]));
	}
	if (data->hooks & G_KEY)
	{
		data->camera->rotation.val[1] -= 2;
		data->rot_mat[1] = init_rotation_matrix_y(degree_to_radian(data->camera->rotation.val[1]));
	}
	if (data->hooks & (W_KEY | S_KEY))
	{
		t_3vecf dir = mult_3vecf_33matf(assign_3vecf(0, 0, 0.2), data->rot_mat[1]);
//		printf("%f %f %f\n", dir.val[0], dir.val[1], dir.val[2]);
		if (data->hooks & A_KEY)
			data->camera->origin.val[0] -= 0.2;
		if (data->hooks & D_KEY)
			data->camera->origin.val[0] += 0.2;
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

		//	data->camera->origin.val[2] -= 0.2;
	}
	if (data->hooks & (A_KEY | D_KEY))
	{
		t_3vecf dir = mult_3vecf_33matf(assign_3vecf(0.2, 0, 0), data->rot_mat[1]);
//		printf("%f %f %f\n", dir.val[0], dir.val[1], dir.val[2]);
		if (data->hooks & A_KEY)
		{
			data->camera->origin.val[0] -= dir.val[0];
			data->camera->origin.val[1] -= dir.val[1];
			data->camera->origin.val[2] -= dir.val[2];
		}

		//	data->camera->origin.val[0] -= 0.2;
		if (data->hooks & D_KEY)
		{
			data->camera->origin.val[0] += dir.val[0];
			data->camera->origin.val[1] += dir.val[1];
			data->camera->origin.val[2] += dir.val[2];
		}

		//	data->camera->origin.val[0] += 0.2;
	}
}
/*
void	loop_manage_rot_matrix(t_data *data)
{
	if (data->params.p_rotcam_z && !data->params.m_rotcam_z)
		data->mats.teta_z += data->speed;
	else if (data->params.m_rotcam_z && !data->params.p_rotcam_z)
		data->mats.teta_z -= data->speed;
	if (data->params.p_rotcam_x && !data->params.m_rotcam_x)
		data->mats.teta_x += data->speed;
	else if (data->params.m_rotcam_x && !data->params.p_rotcam_x)
		data->mats.teta_x -= data->speed;
	free_matrix(&data->mats.rot_x);
	free_matrix(&data->mats.rot_z);
	free_matrix(&data->mats.world_mat);
	free_matrix(&data->mats.proj_mat);
	data->mats.rot_x = get_rot_x(data->mats.teta_x);
	data->mats.rot_z = get_rot_z(data->mats.teta_z);
	data->mats.world_mat = get_world_matrix(data->cam.from, data);
	if (data->proj == PERSP)
		data->mats.proj_mat = get_projection_matrix(data->cam.fov,
			data->cam.near, data->cam.far);
	else if (data->proj == ORTO)
		data->mats.proj_mat = get_ortho_matrix(data);
}
*/
int		print_loop_image(void *param)
{
	t_data *data;

	data = (t_data *)param;

//	printf("%x\n", data->hooks);
//	loop_manage_speed(data);
//	loop_manage_render(data);
	loop_manage_cam(data);
//	loop_manage_rot_matrix(data);
	mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img_ptr);
	data->mlx->img_ptr = mlx_new_image(data->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->mlx->img_str = (int *)mlx_get_data_addr(data->mlx->img_ptr,
			&(data->mlx->bpp), &(data->mlx->s_l), &(data->mlx->endian));
//	display_points(data->pix_map, data->map, data);
//	link_pixels(data->pix_map, data);
	//write(1, "lol\n", 4);
	render(data);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->mlx->img_ptr, 0, 0);
	return (1);
}
