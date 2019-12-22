/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrix.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/21 22:36:28 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/22 08:18:26 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

void	mult_vec_matrix(t_3vecf vect, t_44matf mat, t_3vecf *dst)
{ 
	float	a;
	float	b;
	float	c;
	float	w;

	a = vect.val[0] * mat.val[0][0] + vect.val[1] * mat.val[1][0] + vect.val[2] * mat.val[2][0] + mat.val[3][0];
	b = vect.val[0] * mat.val[0][1] + vect.val[1] * mat.val[1][1] + vect.val[2] * mat.val[2][1] + mat.val[3][1];
	c = vect.val[0] * mat.val[0][2] + vect.val[1] * mat.val[1][2] + vect.val[2] * mat.val[2][2] + mat.val[3][2];
	w = vect.val[0] * mat.val[0][3] + vect.val[1] * mat.val[1][3] + vect.val[2] * mat.val[2][3] + mat.val[3][3];

	dst->val[0] = a / w;
	dst->val[1] = b / w;
	dst->val[2] = c / w;
} 

void	mult_dir_matrix(t_3vecf vect, t_44matf mat, t_3vecf *dst)
{ 
	dst->val[0] = vect.val[0] * mat.val[0][0] + vect.val[1] * mat.val[1][0] + vect.val[2] * mat.val[2][0];
	dst->val[1] = vect.val[0] * mat.val[0][1] + vect.val[1] * mat.val[1][1] + vect.val[2] * mat.val[2][1];
	dst->val[2] = vect.val[0] * mat.val[0][2] + vect.val[1] * mat.val[1][2] + vect.val[2] * mat.val[2][2];
} 

void		init_light_to_world_matrix(float mat[4][4])
{
	mat[0][0] = 11.146836;
	mat[0][1] = -5.781569;
	mat[0][2] = -0.0605886;
	mat[0][3] = 0;
	mat[1][0] = -0.199534;
	mat[1][1] = -3.543982;
	mat[1][2] = -11.89;
	mat[1][3] = 0;
	mat[2][0] = 5.459;
	mat[2][1] = 10.568624;
	mat[2][2] = -4.0220;
	mat[2][3] = 0;
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}

void		init_camera_to_world_matrix(float mat[4][4])
{
	mat[0][0] = 0.945519;
	mat[0][1] = 0;
	mat[0][2] = -0.325569;
	mat[0][3] = 0;
	mat[1][0] = -0.179534;
	mat[1][1] = 0.834209;
	mat[1][2] = -0.521403;
	mat[1][3] = 0;
	mat[2][0] = 0.271593;
	mat[2][1] = 0.551447;
	mat[2][2] = 0.78876;
	mat[2][3] = 0;
	mat[3][0] = 4.208271;
	mat[3][1] = 8.374532;
	mat[3][2] = 17.932925;
	mat[3][3] = 1;
}
