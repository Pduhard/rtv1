/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cone.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/30 18:21:18 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/30 20:50:19 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"
// http://www.illusioncatalyst.com/notes_files/mathematics/line_cone_intersection.php
t_3vecf	get_normal_intersect_cone(t_3vecf inter_point, t_obj *cone)
{
	t_plane *param;

	param = (t_plane *)plane->obj_param;
	return (t_3vecf(0, 0, 0));
	(void)inter_point;
}

int	ray_intersect_cone(t_3vecf orig, t_3vecf dir, t_obj *cone, float *dist, float min_dist, float max_dist)
{

	return (0);
}

int		parse_cone(char *line, t_data *data)
{
	int			i;
	t_obj		*plane;
	t_plane		*plane_param;

	if (!(plane = malloc(sizeof(t_obj))) || !(plane_param = malloc(sizeof(t_plane))))
		return (0);
	i = 5;
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &plane_param->origin)) == -1)
	{
		ft_printf("Syntax error: cone syntax: cone(origin)(normal)(color)\n");
		return (0);
	}
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &plane_param->normal)) == -1)
	{
		ft_printf("Syntax error: cone syntax: cone(origin)(normal)(color)\n");
		return (0);
	}
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &plane->color)) == -1)
	{
		ft_printf("Syntax error: cone syntax: cone(origin)(normal)(color)\n");
		return (0);
	}
	printf("plane : %f %f %f && %f %f %f && %f %f %f\n", plane_param->origin.val[0], plane_param->origin.val[1], plane_param->origin.val[2], plane_param->normal.val[0], plane_param->normal.val[1], plane_param->normal.val[2] , plane->color.val[0], plane->color.val[1], plane->color.val[2]);
	plane->obj_param = plane_param;
	plane->obj_type = OBJ_PLANE;
	plane->ray_intersect = &ray_intersect_plane;
	plane->get_normal_inter = &get_normal_intersect_plane;
	if (data->objs)
	{
		plane->next = data->objs;
	}
	else
		plane->next = NULL;
	data->objs = plane;
	return (1);
}
