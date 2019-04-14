#include "ft_ls.h"

void	display_fi(t_ls ls, t_fi *fi)
{
	// struct dirent	*dp;
	t_fi			*temp;
	int			folder_print;

	folder_print = get_fi_len(fi) > 1;
	// fi_set_to_head(&fi);
	while (fi)
	{
		temp = fi;
		if (fi->dirp)
		{
			folder_print ? printf("%s:\n", fi->name) : 0;
			handle_dp_data(fi->dirp, ls);
			printf("\n\n");
		}
		else
			printf("%s\n\n", fi->name);
		fi = fi->next;
		// free(temp);
	}
}

void	display_curr(t_ls ls, t_fi *fi)
{
	struct dirent	*dp;

	while((dp = readdir(fi->dirp)) != NULL)
		ft_start_with(dp->d_name, '.') ? 0 :
		printf("%s%c", dp->d_name, IS_one_FLAG(ls.flag) ? '\n' : '\t');
	printf("\n");
	free(fi);
}
