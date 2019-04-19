/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:45:05 by hnam              #+#    #+#             */
/*   Updated: 2019/04/16 23:53:18 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error_alert(int type, char *input)
{
	if (type == INVALID_INPUT)
		ft_printf("ft_ls: %s: No such file or directory\n", input);
}

void	error_exit(int type, char *input)
{
	if (type == INVALID_FLAG)
		ft_printf("ft_ls: illegal option -- %c\nusage: ls [-%s] [file ...]\n",
			input[0], VALID_FLAG);
	exit(0);
}
