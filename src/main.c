#include "ft_ls.h"

int	main(int ac, char *av[])
{
	t_ls			*ls;

	// DIR				*dirp;
	// struct dirent	*dp;
	// struct stat		info;
	int				i;


	// if (av[1])
	// 	flag_handelr(av[1]);
	i = 1;
	while (i < ac)
	{
		if (ft_start_with(av[i], '-'))
			get_ls_flag(&av[i++][1]);
	}
	// if (av[i] && ft_start_with(av[i], '-'))
	// 	get_ls_flag(&av[i++][1]);
	// if (ac >= 2)

	dirp = opendir(ac == i ? av[i] : "."); // va_arg
	lstat(av[1], &info);
	printf("%ld\n", info.st_mtime);

	if (dirp == NULL)
	{
		printf("ft_ls: %s: No such file or directory\n", av[1]);
		return (0);
	}
	// len = ft_strlen(av[1]);
	// info = malloc(sizeof(struct stat));

	while ((dp = readdir(dirp)) != NULL)
	{
		printf("name : %s\ttype %hhu\n", dp->d_name,dp->d_type); // name
		// printf("ino: %llu\n", dp->d_ino);
		// printf("nam_len : %d\n", dp->d_namlen);
		// printf("rec_len: %d\n", dp->d_reclen); //  length of this record
		printf("rec_len: %llu\n", dp->d_seekoff);
		// printf("type %lu\n", dp->d_type);//file type,
// // 			#define	DT_UNKNOWN	 0
// 		// #define	DT_FIFO		 1
// 		// #define	DT_CHR		 2
// 		// #define	DT_DIR		 4
// 		// #define	DT_BLK		 6
// 		// #define	DT_REG		 8
// 		// #define	DT_LNK		10
// 		// #define	DT_SOCK		12
// 		// #define	DT_WHT		14
			lstat(dp->d_name, &info);
// 			// int size = buf.st_size;
// 			printf("st_gen%u\n", info.st_gen);
			printf("time\t%s\n", (ctime(&(info.st_mtime))));
			printf("mode \t%s\n", ft_itoa_base(info.st_mode,2,0));
			// printf("mode \t%s\n", ft_itoa_base(info.st_mode,8,0));
			// // printf("mode \t%s\n", ft_itoa_base(info.st_mode, 8, 0));
			// printf("mode \t%d\n", (info.st_mode & S_IRUSR));
			// printf("mode \t%d\n", S_IRUSR);
			printf("%5d\n", info.st_nlink);
			printf("%s\n", (getpwuid(info.st_uid))->pw_name);
			// // (getpwuid(info.st_uid))->pw_uid);
			printf("%s\n", (getgrgid(info.st_gid))->gr_name);
			// // printf("gett-")
			printf("st_size%lld\n",info.st_size);

		// if (dp->d_name[0] == 'i')
		// if (dp->d_namlen == len && strcmp(dp->d_name, name) == 0)
		// {

		// 	(void)closedir(dirp);
		// 	return (0);
		// }
	}
	(void)closedir(dirp);
	return (0);
}
