/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/23 09:57:29 by aplat        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 10:12:27 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

void			free_all(t_data *data)
{
	if (data->mlx)
	{
		mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img_ptr);
		mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->win_ptr);
	}
	if (data->scene_name)
		free(data->scene_name);
	if (data->camera)
		free(data->camera);
	free_objs(data->objs);
	free_lights(data->lights);
	free(data);
}

void			free_objs(t_obj *objs)
{
	t_obj		*next;

	if (!objs)
		return ;
	while (objs)
	{
		next = objs->next;
		free(objs->obj_param);
		free(objs);
		objs = next;
	}
}

void			free_lights(t_light *lights)
{
	t_light		*next;

	if (!lights)
		return ;
	while (lights)
	{
		next = lights->next;
		lights = next;
	}
}
