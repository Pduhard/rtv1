/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cylinder.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/13 20:10:21 by aplat        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 14:59:26 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

/*
** http://www.illusioncatalyst.com/notes_files/
**		mathematics/line_cylinder_intersection.php
*/

t_polynome	polynome_cylinder(t_3vecf orig, t_3vecf dir, t_cylinder c)
{
	t_polynome	poly;

	poly.w = sub_3vecf(orig, c.center);
	poly.dp_dir_norm_h = dot_product_3vecf(dir, c.norm_h);
	poly.dp_w_norm_h = dot_product_3vecf(poly.w, c.norm_h);
	poly.a = dot_product_3vecf(dir, dir) - poly.dp_dir_norm_h
		* poly.dp_dir_norm_h;
	poly.b = 2 * (dot_product_3vecf(dir, poly.w) - poly.dp_dir_norm_h
		* poly.dp_w_norm_h);
	poly.c = dot_product_3vecf(poly.w, poly.w) - poly.dp_w_norm_h
		* poly.dp_w_norm_h - c.radius2;
	poly.delta = poly.b * poly.b - 4 * poly.a * poly.c;
	return (poly);
}

void		set_cylinder(t_cylinder *c)
{
	c->h = sub_3vecf(c->center, c->tip);
	c->norm_h = c->h;
	normalize_3vecf(&c->norm_h);
	c->radius2 = c->radius * c->radius;
}

t_3vecf		get_normal_intersect_cylinder(t_3vecf inter_point, t_obj *cylinder)
{
	t_cylinder	*cylinder_param;
	t_3vecf		ch;
	t_3vecf		cp;
	float		step_inter_proj;
	float		inter_proj_dist;

	cylinder_param = (t_cylinder *)cylinder->obj_param;
	cp = sub_3vecf(inter_point, cylinder_param->center);
	ch = sub_3vecf(cylinder_param->tip, cylinder_param->center);
	inter_proj_dist = dot_product_3vecf(ch, cp) / get_length_3vecf(ch);
	step_inter_proj = inter_proj_dist / get_length_3vecf(ch);
	return (sub_3vecf(productadd_3vecf(
		cylinder_param->center, ch, step_inter_proj), inter_point));
}

int			ray_intersect_cylinder(t_3vecf orig, t_3vecf dir,
		t_obj *cylinder, t_dist dist)
{
	t_cylinder	*cylinder_param;
	t_polynome	poly;

	cylinder_param = (t_cylinder *)cylinder->obj_param;
	poly = polynome_cylinder(orig, dir, *cylinder_param);
	if (solve_quadra(poly, dist.closest_dist, dist.min_dist,
		dist.max_dist) == 0)
		return (0);
	return (1);
}

int			parse_cylinder(char *line, t_data *data)
{
	int			i;
	t_obj		*cylinder;
	t_cylinder	*cylinder_param;

	if (!(cylinder = malloc(sizeof(t_obj)))
		|| !(cylinder_param = malloc(sizeof(t_cylinder))))
		return (0);
	i = 8;
	if (!(syntax_cylinder(line, i, cylinder_param, &cylinder->color)))
		return (0);
	cylinder->obj_param = cylinder_param;
	cylinder->obj_type = OBJ_CYLINDER;
	set_cylinder(cylinder->obj_param);
	cylinder->ray_intersect = &ray_intersect_cylinder;
	cylinder->get_normal_inter = &get_normal_intersect_cylinder;
	if (data->objs)
		cylinder->next = data->objs;
	else
		cylinder->next = NULL;
	data->objs = cylinder;
	return (1);
}
