/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:44:01 by hnam              #+#    #+#             */
/*   Updated: 2019/04/16 21:44:03 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fi_set_to_head(t_fi **fi)
{
	while ((*fi)->prev)
		(*fi) = (*fi)->prev;
}

int		get_fi_len(t_fi *fi)
{
	int len;

	len = 0;
	while (fi->next)
	{
		fi = fi->next;
		len++;
	}
	return (len);
}

void	dp_set_to_head(t_dp **dp)
{
	while ((*dp)->prev)
		(*dp) = (*dp)->prev;
}

int		get_dp_len(t_dp *dp)
{
	int len;

	len = 0;
	while (dp->next)
	{
		dp = dp->next;
		len++;
	}
	return (len);
}

int		is_hidden(char *name)
{
	if (ft_strcmp(name, ".") == 0)
		return (1);
	if (ft_strcmp(name, "..") == 0)
		return (1);
	return (0);
}
