#include "../include/nm.h"

/**
 * @brief Extract file from command line
 * @param argc number of arguments
 * @param argv arguments
 * @return list of files
 */
t_list *extract_file_from_cmd(int argc, char **argv)
{
	t_list *lst = NULL;

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(argv[i])));
		}
	}
	if (!lst) {
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup("a.out")));
	}
	return (lst);
}