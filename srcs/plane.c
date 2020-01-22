/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   plane.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/30 17:05:21 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 14:48:10 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

t_3vecf		get_normal_intersect_plane(t_3vecf inter_point, t_obj *plane)
{
	t_plane	*param;

	param = (t_plane *)plane->obj_param;
	return (param->normal);
	(void)inter_point;
}

int			ray_intersect_plane(t_3vecf orig, t_3vecf dir, t_obj *plane,
	t_dist dist)
{
	t_plane	*p;
	float	div;
	float	inter_dist;

	p = (t_plane *)plane->obj_param;
	div = dot_product_3vecf(dir, p->normal);
	if (div == 0)
		return (0);
	inter_dist = dot_product_3vecf(sub_3vecf(p->origin, orig), p->normal) / div;
	if (inter_dist < *dist.closest_dist && inter_dist > dist.min_dist
		&& inter_dist < dist.max_dist)
	{
		*dist.closest_dist = inter_dist;
		return (1);
	}
	return (0);
}

int			parse_plane(char *line, t_data *data)
{
	int		i;
	t_obj	*plane;
	t_plane	*plane_param;

	if (!(plane = malloc(sizeof(t_obj)))
		|| !(plane_param = malloc(sizeof(t_plane))))
		return (0);
	i = 5;
	if (!(syntax_plane(line, i, plane_param, &plane->color)))
		return (0);
	plane->obj_param = plane_param;
	plane->obj_type = OBJ_PLANE;
	plane->ray_intersect = &ray_intersect_plane;
	plane->get_normal_inter = &get_normal_intersect_plane;
	if (data->objs)
		plane->next = data->objs;
	else
		plane->next = NULL;
	data->objs = plane;
	return (1);
}
