#include "ft_ls.h"

void	error_alert(int type, char *input)
{
	if (type == INVALID_INPUT)
		printf("ft_ls: %s: No such file or directory\n", input);
}

void	error_exit(int type, char *input)
{
	if (type == INVALID_FLAG)
		printf("ft_ls: illegal option -- %c\nusage: ls [-%s] [file ...]\n",
			 input[0], VALID_FLAG);
	exit(0);
}
