#include "ft_ls.h"

int get_ls_flag(char *flags)
{
	int	flag;

	flag = 0;
	while (*flags)
	{
		if (ft_strchr(VALID_FALG, *flags) == NULL)
			return (-1);
		flag = *flags == '1' ? flag | one_FLAG : flag;
		flag = *flags == 'l' ? flag | l_FLAG : flag;
		flag = *flags == 'a' ? flag | a_FLAG : flag;
		flag = *flags == 'r' ? flag | r_FLAG : flag;
		flag = *flags == 'R' ? flag | R_FLAG : flag;
		flag = *flags == 't' ? flag | t_FLAG : flag;
		flag = *flags == 'S' ? flag | S_FLAG : flag;
		flags++;
	}
	printf("%s\n", ft_itoa_base(flag, 2, 0));
	return flag;
}
