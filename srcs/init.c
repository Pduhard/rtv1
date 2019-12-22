/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/21 22:19:28 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/22 08:21:58 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

static t_mlx	*init_mlx(void)
{
	t_mlx	*mlx;

	if (!(mlx = malloc(sizeof(t_mlx))))
		return (NULL);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "rtv1");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT);
	mlx->img_str = (int *)mlx_get_data_addr(mlx->img_ptr,
			&(mlx->bpp), &(mlx->s_l), &(mlx->endian));
	return (mlx);
}

t_data	*init_data(void)
{
	t_data	*data;
	t_sphere	*param;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	if (!(data->objs = malloc(sizeof(t_obj))))
	{
		free(data);
		return (NULL);
	}
	if (!(data->mlx = init_mlx()))
	{
		free(data->objs);
		free(data);
		return (NULL);	
	}
	if (!(data->objs->obj_param = malloc(sizeof(t_sphere))))
	{
		free(data->objs);
		free(data);
		return (NULL);
	}
	if (!(data->lights = malloc(sizeof(t_light))))
	{
		free(data->objs);
		free(data);
		return (NULL);
	}
	data->lights->intensity = assign_3vecf(2,2,2);
	data->lights->position = assign_3vecf(4,3, -17);
	param = (t_sphere *)data->objs->obj_param;
	param->x = -4;
	param->y = -8;
	param->z = 8;
	param->radius = 4;
	data->objs->color = 0xff0000;
	init_camera_to_world_matrix(data->camera_to_world.val);
	init_light_to_world_matrix(data->lights->l_to_world.val);
	data->lights->color = assign_3vecf(1, 1, 1);
	data->fov = 51.12;
	return (data);
}
