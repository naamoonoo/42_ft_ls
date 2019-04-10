/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 00:29:09 by hnam              #+#    #+#             */
/*   Updated: 2019/04/04 01:07:04 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	time_print(va_list *ap, t_s fs)
{
	char		*form;
	time_t		now;
	int			len;
	struct tm	*t_f;

	form = va_arg(*ap, char *);
	now = time(NULL);
	t_f = localtime(&now);
	len = fs.width;
	if (form[0] == 'C')
	{
		ft_printf("%d-%02d-%02d", 1900 + t_f->tm_year,
			t_f->tm_mon + 1, t_f->tm_mday + 1);
		len += 10;
	}
	if (form[1] == 'T')
	{
		form[0] == 'C' ? ft_putchar(' ') : 0;
		ft_printf("%02d:%02d:%02d", t_f->tm_hour,
			t_f->tm_min, t_f->tm_sec);
		len += 8;
	}
	return (get_big(fs.width, len));
}
