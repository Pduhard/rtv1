/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sphere.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/30 16:52:54 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 14:49:43 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

t_polynome	polynome_sphere(t_3vecf dir, t_sphere s, t_3vecf dist)
{
	t_polynome	poly;

	poly.a = dot_product_3vecf(dir, dir);
	poly.b = 2.f * dot_product_3vecf(dist, dir);
	poly.c = dot_product_3vecf(dist, dist) - s.radius * s.radius;
	poly.delta = poly.b * poly.b - 4.f * poly.a * poly.c;
	return (poly);
}

t_3vecf		get_normal_intersect_sphere(t_3vecf inter_point, t_obj *sphere)
{
	t_sphere	*param;

	param = (t_sphere *)sphere->obj_param;
	return (sub_3vecf(inter_point, param->origin));
}

int			ray_intersect_sphere(t_3vecf orig, t_3vecf dir, t_obj *sphere,
	t_dist dist)
{
	t_3vecf		dist_vec;
	t_sphere	*sphere_param;
	t_polynome	poly;

	sphere_param = (t_sphere *)sphere->obj_param;
	dist_vec = sub_3vecf(orig, sphere_param->origin);
	poly = polynome_sphere(dir, *sphere_param, dist_vec);
	if (solve_quadra(poly, dist.closest_dist, dist.min_dist,
		dist.max_dist) == 0)
		return (0);
	return (1);
}

int			parse_sphere(char *line, t_data *data)
{
	int			i;
	t_obj		*sphere;
	t_sphere	*sphere_param;

	if (!(sphere = malloc(sizeof(t_obj)))
		|| !(sphere_param = malloc(sizeof(t_sphere))))
		return (0);
	i = 6;
	if (!(syntax_sphere(line, i, sphere_param, &sphere->color)))
		return (0);
	sphere->obj_param = sphere_param;
	sphere->obj_type = OBJ_SPHERE;
	sphere->ray_intersect = &ray_intersect_sphere;
	sphere->get_normal_inter = &get_normal_intersect_sphere;
	if (data->objs)
		sphere->next = data->objs;
	else
		sphere->next = NULL;
	data->objs = sphere;
	return (1);
}
