/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cone.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/30 18:21:18 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 14:47:44 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

/*
** http://www.illusioncatalyst.com/notes_files/
**			mathematics/line_cone_intersection.php
*/

t_polynome		polynome_cone(t_3vecf orig, t_3vecf dir, t_cone c)
{
	t_polynome	poly;

	poly.w = sub_3vecf(orig, c.tip);
	poly.dp_dir_norm_h = dot_product_3vecf(dir, c.norm_h);
	poly.dp_w_norm_h = dot_product_3vecf(poly.w, c.norm_h);
	poly.a = dot_product_3vecf(dir, dir) - c.m * poly.dp_dir_norm_h
		* poly.dp_dir_norm_h - poly.dp_dir_norm_h * poly.dp_dir_norm_h;
	poly.b = 2 * (dot_product_3vecf(dir, poly.w) - c.m * poly.dp_dir_norm_h
		* poly.dp_w_norm_h - poly.dp_dir_norm_h * poly.dp_w_norm_h);
	poly.c = dot_product_3vecf(poly.w, poly.w) - c.m * poly.dp_w_norm_h
		* poly.dp_w_norm_h - poly.dp_w_norm_h * poly.dp_w_norm_h;
	poly.delta = poly.b * poly.b - 4 * poly.a * poly.c;
	return (poly);
}

void			set_cone(t_cone *c)
{
	c->h = sub_3vecf(c->center, c->tip);
	c->norm_h = c->h;
	normalize_3vecf(&c->norm_h);
	c->h_length = get_length_3vecf(c->h);
	c->m = (c->radius * c->radius) / (c->h_length * c->h_length);
}

t_3vecf			get_normal_intersect_cone(t_3vecf inter_point, t_obj *cone)
{
	float		intersect;
	t_cone		*c;
	t_3vecf		hp;
	t_3vecf		cp;
	t_3vecf		tmp;

	c = (t_cone *)cone->obj_param;
	c->h = sub_3vecf(c->center, c->tip);
	intersect = dot_product_3vecf(sub_3vecf(inter_point, c->tip), c->h);
	hp = sub_3vecf(c->tip, inter_point);
	cp = sub_3vecf(c->center, inter_point);
	tmp = product_3vecf(hp, product_3vecf(hp, cp));
	if (intersect < 0)
		return (invert_3vecf(tmp));
	else
		return (tmp);
}

int				ray_intersect_cone(t_3vecf orig, t_3vecf dir, t_obj *cone,
				t_dist dist)
{
	t_cone		*cone_param;
	t_polynome	poly;

	cone_param = (t_cone *)cone->obj_param;
	poly = polynome_cone(orig, dir, *cone_param);
	if (solve_quadra(poly, dist.closest_dist, dist.min_dist,
		dist.max_dist) == 0)
		return (0);
	return (1);
}

int				parse_cone(char *line, t_data *data)
{
	int			i;
	t_obj		*cone;
	t_cone		*cone_param;

	if (!(cone = malloc(sizeof(t_obj)))
		|| !(cone_param = malloc(sizeof(t_cone))))
		return (0);
	i = 4;
	if (!(syntax_cone(line, i, cone_param, &cone->color)))
		return (0);
	cone->obj_param = cone_param;
	cone->obj_type = OBJ_CONE;
	set_cone(cone->obj_param);
	cone->ray_intersect = &ray_intersect_cone;
	cone->get_normal_inter = &get_normal_intersect_cone;
	if (data->objs)
		cone->next = data->objs;
	else
		cone->next = NULL;
	data->objs = cone;
	return (1);
}
