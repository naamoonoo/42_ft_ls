/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:31:49 by hnam              #+#    #+#             */
/*   Updated: 2019/04/14 13:09:00 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

//
# include <stdio.h>
//

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

// #define	DT_UNKNOWN	 0
// #define	DT_FIFO		 1
// #define	DT_CHR		 2
// #define	DT_DIR		 4 // folder
// #define	DT_BLK		 6
// #define	DT_REG		 8 // excute
// #define	DT_LNK		10
// #define	DT_SOCK		12
// #define	DT_WHT		14
# define VALID_FLAG "1larRtS"
# define NUM_OF_FLAG ((int)ft_strlen(VALID_FLAG))

# define INVALID_INPUT -42
# define INVALID_FLAG -4242

# define IS_one_FLAG(flag) (((flag & one_FLAG) == one_FLAG))
# define IS_l_FLAG(flag) (((flag & l_FLAG) == l_FLAG))
# define IS_a_FLAG(flag) (((flag & a_FLAG) == a_FLAG))
# define IS_r_FLAG(flag) (((flag & r_FLAG) == r_FLAG))
# define IS_R_FLAG(flag) (((flag & R_FLAG) == R_FLAG))
# define IS_t_FLAG(flag) (((flag & t_FLAG) == t_FLAG))
# define IS_S_FLAG(flag) (((flag & S_FLAG) == S_FLAG))

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
	struct s_dp		*next;
	struct s_dp		*prev;
}					t_dp;

typedef struct		s_ls
{
	t_fi			*fi;
	int				flag;
	int				len;
	char			*curr;
}					t_ls;

void				make_linked_fi(char *name, t_ls *ls, int *f_count);
void				ft_ls(t_ls ls, char *name, int root_show);

int					get_ls_flag(char *flags, int *counter);

// void				make_linked_data(struct dirent *p, t_dp **dp, int start);
void				make_linked_data(struct dirent *p, t_dp **dp, int start, char *name);



t_fi				*get_fi_data(char *av[], t_ls *ls);
void				link_fi_data(char *name, DIR *dirp, struct stat info,
					t_fi **fi, int *arg_started);

void				fi_set_to_head(t_fi **fi);
int					get_fi_len(t_fi *fi);


void				swap_fi(t_fi **fi);
void				sort_fi(t_fi **fi);

void				swap_dp(t_dp **dp);
void				sort_dp(t_dp **dp, t_ls *ls);
void				dp_set_to_head(t_dp **dp);
int					get_dp_len(t_dp *dp);
void	handle_dp_data(DIR *dirp, t_ls ls);
void	link_dp(t_dp **dp, struct dirent *p);
void	display_dp(t_dp *dp, t_ls ls);

int		is_hidden(char *name);


void				display_fi(t_ls ls, t_fi *fi);
void				display_curr(t_ls ls, t_fi *fi);

void				error_alert(int type, char *input);
void				error_exit(int type, char *input);


#endif
