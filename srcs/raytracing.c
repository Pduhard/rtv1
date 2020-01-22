/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raytracing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/21 04:37:40 by aplat        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 14:49:27 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

t_3vecf	ray_trace(t_3vecf orig, t_3vecf dir,
		t_dist dist, t_data *data)
{
	float		closest_dist;
	t_obj		*closest_obj;
	t_3vecf		inter_point;
	t_3vecf		normal_inter;
	float		light_fact;

	dist.closest_dist = &closest_dist;
	closest_obj = ray_first_intersect(orig,
		dir, dist, data->objs);
	if (!closest_obj)
		return (assign_3vecf(0, 0, 0));
	inter_point = productadd_3vecf(orig, dir, closest_dist);
	normal_inter = closest_obj->get_normal_inter(inter_point, closest_obj);
	normalize_3vecf(&normal_inter);
	if (dot_product_3vecf(normal_inter, dir) > 0)
		normal_inter = invert_3vecf(normal_inter);
	light_fact = compute_lights(inter_point, normal_inter,
		invert_3vecf(dir), (t_to_loop){data->lights, data->objs});
	return (productwf_3vecf(closest_obj->color, light_fact));
}

t_obj	*ray_first_intersect(t_3vecf orig, t_3vecf dir,
		t_dist dist, t_obj *objs)
{
	t_obj	*closest_obj;

	closest_obj = NULL;
	*dist.closest_dist = FLT_MAX;
	while (objs)
	{
		if (objs->ray_intersect(orig, dir, objs, dist))
			closest_obj = objs;
		objs = objs->next;
	}
	return (closest_obj);
}
