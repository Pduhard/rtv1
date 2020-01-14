/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cylinder.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/13 20:10:21 by aplat        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 09:25:01 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"
// http://www.illusioncatalyst.com/notes_files/mathematics/line_cylinder_intersection.php

t_3vecf	get_normal_intersect_cylinder(t_3vecf inter_point, t_obj *cylinder)
{
	float	intersect;
	t_3vecf	h;

	t_cylinder	*cylinder_param;
	t_3vecf	hp;
	t_3vecf	cp;
	t_3vecf	tang;
	t_3vecf	tmp;

	cylinder_param = (t_cylinder *)cylinder->obj_param;
	h = sub_3vecf(cylinder_param->center, cylinder_param->tip);
	intersect = dot_product_3vecf(sub_3vecf(inter_point, cylinder_param->center), h);
	hp = sub_3vecf(cylinder_param->tip, inter_point);
	cp = sub_3vecf(cylinder_param->center, inter_point);
	tang = product_3vecf(hp, cp);
	tmp = product_3vecf(hp, tang);
	if (intersect < 0)
		return (assign_3vecf(-tmp.val[0], -tmp.val[1], -tmp.val[2]));
	else
		return (tmp);
	(void)inter_point;
}

int ray_intersect_cylinder(t_3vecf orig, t_3vecf dir, t_obj *cylinder, float *dist, float min_dist, float max_dist)
{
	t_3vecf	h;
	t_3vecf	norm_h;
//	float	h_length;
	float	a;
	float	b;
	float	c;
	int		check = 0;
	t_cylinder	*cylinder_param;

	cylinder_param = (t_cylinder *)cylinder->obj_param;
	h = sub_3vecf(cylinder_param->center, cylinder_param->tip);
	norm_h = h;
	normalize_3vecf(&norm_h);
//	h_length = get_lenght_3vecf(h);

	float	dp_dir_norm_h;
	float	dp_w_norm_h;
	t_3vecf	w;

	w = sub_3vecf(orig, cylinder_param->center);
	dp_dir_norm_h = dot_product_3vecf(dir, norm_h);
	dp_w_norm_h = dot_product_3vecf(w, norm_h);

	a = dot_product_3vecf(dir, dir) - dp_dir_norm_h * dp_dir_norm_h;
	b = 2 * (dot_product_3vecf(dir, w) - dp_dir_norm_h * dp_w_norm_h);
	c = dot_product_3vecf(w, w) - dp_w_norm_h * dp_w_norm_h - cylinder_param->radius * cylinder_param->radius;

	float	delta;
	delta = b * b - 4 * a * c;
	t_2vecf	hit_point;

	if (delta > 0)
	{
		hit_point.val[0] = (-b + sqrtf(delta)) / (2 * a);
		hit_point.val[1] = (-b - sqrtf(delta)) / (2 * a);
		if (hit_point.val[0] < *dist && hit_point.val[0] > min_dist && hit_point.val[0] < max_dist)
		{
			check = 1;
			*dist = hit_point.val[0];
		}
		if (hit_point.val[1] < *dist && hit_point.val[1] > min_dist && hit_point.val[1] < max_dist)
		{
			check = 1;
			*dist = hit_point.val[1];
		}
		return (check);
	}
	return (0);
}

int			parse_cylinder(char *line, t_data *data)
{
	int			i;
	t_obj		*cylinder;
    t_cylinder	*cylinder_param;

	if (!(cylinder = malloc(sizeof(t_obj))) || !(cylinder_param = malloc(sizeof(t_cylinder))))
		return (0);
	i = 8;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &cylinder_param->center)) == -1)
	{
		ft_printf("Syntax error: cylinder syntax: cylinder(center)(tip)(radius)\n");
		return (0);
	}
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &cylinder_param->tip)) == -1)
	{
		ft_printf("Syntax error: cylinder syntax: cylinder(center)(tip)(radius)\n");
		return (0);
	}
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_float(line, i, &cylinder_param->radius)) == -1)
	{
		ft_printf("Syntax error: cylinder syntax: cylinder(center)(tip)(radius)\n");
		return (0);
	}
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &cylinder->color)) == -1)
	{
		ft_printf("Syntax error: cylinder syntax: cylinder(center)(tip)(radius)\n");
		return (0);
	}
	cylinder->obj_param = cylinder_param;
	cylinder->obj_type = OBJ_CYLINDER;
	cylinder->ray_intersect = &ray_intersect_cylinder;
	cylinder->get_normal_inter = &get_normal_intersect_cylinder;
	if (data->objs)
		cylinder->next = data->objs;
	else
		cylinder->next = NULL;
	data->objs = cylinder;
	return (1);
}
