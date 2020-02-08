/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 13:27:33 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 11:55:01 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft/libft.h"

typedef enum	e_error
{
	MALLOC_FAIL = 5,
	EXIT = 6
}				t_error;

typedef enum	e_flags
{
	WIDTH = 1,
	PRECISION = 2,
	ZERO = 4,
	MINUS = 8
}				t_flags;

typedef struct	s_data
{
	int			i;
	char		format;
	char		*flags;
	char		flag_bit;
	char		*output;
	int			value;
	int			precision_nbr;
	int			width_nbr;
	int			star_fprec;
	int			star_fwidth;
	int			star_arg;
	int			star_arg2;
	int			flag_zero;
	char		c;
	int			neg;
	int			neg_i;
	int			nbr_pad;
	int			error;
}				t_data;

int				ft_printf_fd(int fd, const char *str, ...);
int				ft_assign_data(t_data *data);
char			get_format(const char *str, int i);
int				ft_index(t_data *data);
int				ft_id(va_list ap, t_data *data);
int				ft_c(va_list ap, t_data *data);
int				ft_s(va_list ap, t_data *data);
int				ft_p(va_list ap, t_data *data);
int				ft_u(va_list ap, t_data *data);
int				ft_x(va_list ap, t_data *data);
int				ft_x_upper(va_list ap, t_data *data);
int				ft_pourc(va_list ap, t_data *data);
void			get_flags(const char *str, int i, t_data *data);
void			get_flag_bit(t_data *data);
int				ft_launch_flags(t_data *data);
int				ft_precision_s(t_data *data);
void			ft_output(t_data *data, int fd);
int				ft_precision(t_data *data);
void			get_precision_nbr(t_data *data);
void			get_width_nbr(t_data *data);
int				ft_width(t_data *data);
int				ft_zero(t_data *data);
void			ft_minus(t_data *data);
void			ft_free(t_data *data);
int				ft_width_c(t_data *data);
void			ft_output_c(t_data *data, int fd);
int				ft_precision_neg_i(t_data *data);
int				ft_zero_neg_i(t_data *data);
int				ft_star_precision(t_data *data);
int				ft_precision_check_format(t_data *data);
int				ft_precision_empty_output(t_data *data);
int				ft_precision_specific_cases(t_data *data);
int				ft_precision_s(t_data *data);
int				ft_width_check_format(t_data *data);
int				ft_init_nbr_pad(t_data *data);
void			ft_init_neg(t_data *data, int *neg);
int				set_error(t_data *data);

#endif
