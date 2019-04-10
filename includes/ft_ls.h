#ifndef FT_LS_H
# define FT_LS_H

//
# include <stdio.h>
//

# include "libft.h"
# include "ft_printf.h"
// # include <unistd.h>
// # include <dirent.h>
// # include <sys/stat.h>
// # include <time.h>
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
# define VALID_FALG "1larRtS"

enum			e_flag
{
	one_FLAG = 1 << 0,
	l_FLAG = 1 << 1,
	a_FLAG = 1 << 2,
	r_FLAG = 1 << 3,
	R_FLAG = 1 << 4,
	t_FLAG = 1 << 5,
	S_FLAG = 1 << 6,
};

typedef struct	s_file
{
	char		*name;
	int			n_link;
	char		*u_name;
	char		*g_name;
	int			size;
	char		*time;
}				t_file;

typedef struct	s_ls
{
	t_file		*files;
	int			flag;
}				t_ls;
int				get_ls_flag(char *flags);
#endif
