/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:31:49 by hnam              #+#    #+#             */
/*   Updated: 2019/04/16 23:55:22 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../lib/libftprintf/includes/ft_printf.h"
# include "../lib/libftprintf/includes/libft.h"

# include <sys/xattr.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <limits.h>

# define VALID_FLAG "1larRtScTuUfG"
# define NUM_OF_FLAG ((int)ft_strlen(VALID_FLAG))

# define INVALID_INPUT -42
# define INVALID_FLAG -4242

# define IS_SAME(mode, MODE) (((mode & (MODE)) == (MODE)))

# define IS_DIR(name) (opendir(name) != NULL)
# define IS_HIDDEN(name) (ft_start_with(name, '.'))

enum				e_flag
{
	one_FLAG = 1 << 0,
	l_FLAG = 1 << 1,
	a_FLAG = 1 << 2,
	r_FLAG = 1 << 3,
	R_FLAG = 1 << 4,
	t_FLAG = 1 << 5,
	S_FLAG = 1 << 6,
	c_FLAG = 1 << 7,
	T_FLAG = 1 << 8,
	u_FLAG = 1 << 9,
	U_FLAG = 1 << 10,
	f_FLAG = 1 << 11,
	G_FLAG = 1 << 12,
};

typedef struct		s_flags
{
	char			flag;
	int				bin_flag;
}					t_flags;

typedef struct		s_fi
{
	char			*name;
	struct s_fi		*next;
	struct s_fi		*prev;
}					t_fi;

typedef struct		s_dp
{
	char			*name;
	char			*curr;
	id_t			type;
	struct stat		info;
	long int		time_;
	struct s_dp		*next;
	struct s_dp		*prev;
}					t_dp;

typedef struct		s_ls
{
	t_fi			*fi;
	int				flag;
	int				dp_exist;
}					t_ls;

void				make_linked_fi(char *name, t_ls *ls, int *f_count);
void				ft_ls(t_ls ls, char *name, int root_show);
int					get_ls_flag(char *flags, int *counter);
void				make_linked_data(struct dirent *p, t_dp **dp,
						char *name, t_ls *ls);

char				*get_mode(int mode);
void				display_l_form(t_dp *dp, t_ls ls);
void				colored_print(char *name, int mode);
time_t				get_time(struct stat info, t_ls ls);
void				display_name(t_dp *dp, t_ls ls);

void				free_dp(t_dp *dp);
void				sort_by_flag(t_dp **dp, t_ls ls);
void				display_dp(t_dp *dp, t_ls ls);

void				fi_set_to_head(t_fi **fi);
int					get_fi_len(t_fi *fi);
void				swap_fi(t_fi **fi);
void				sort_fi(t_fi **fi);

void				swap_dp(t_dp **dp);
void				sort_dp(t_dp **dp, t_ls ls, char *name, int root_show);
void				dp_set_to_head(t_dp **dp);
int					get_dp_len(t_dp *dp);
int					is_hidden(char *name);

void				error_alert(int type, char *input);
void				error_exit(int type, char *input);

#endif
