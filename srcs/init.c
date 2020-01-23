/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/21 22:19:28 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 11:50:23 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

void			init_threads(t_thread threads[NB_THREADS], t_data *data)
{
	int			index;

	index = -1;
	while (++index < NB_THREADS)
	{
		threads[index].start = -WIN_WIDTH / 2 + WIN_WIDTH * index / NB_THREADS;
		threads[index].end =
			-WIN_WIDTH / 2 + WIN_WIDTH * (index + 1) / NB_THREADS;
		threads[index].data = data;
	}
}

static t_mlx	*init_mlx(char *name)
{
	t_mlx		*mlx;
	char		*n;

	n = ft_strjoin("RTV1 : ", name);
	if (!(mlx = malloc(sizeof(t_mlx))))
		return (NULL);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, n);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT);
	mlx->img_str = (int *)mlx_get_data_addr(mlx->img_ptr,
			&(mlx->bpp), &(mlx->s_l), &(mlx->endian));
	free(n);
	return (mlx);
}

t_data			*init_data(char *file_name)
{
	t_data		*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	ft_bzero(data, sizeof(t_data));
	if (!(parse_rt_conf(file_name, data)))
	{
		free_all(data);
		return (NULL);
	}
	if (!(data->camera) || !(data->objs) || !(data->lights))
	{
		free_all(data);
		ft_printf("%s : Incomplete rt_conf file\n", file_name);
		return (NULL);
	}
	if (!(data->mlx = init_mlx(data->scene_name)))
	{
		free_all(data);
		return (NULL);
	}
	data->rot_mat[1] =
		init_rotation_matrix_y(degree_to_radian(data->camera->rotation.val[1]));
	data->hooks = 0;
	return (data);
}
