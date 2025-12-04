#ifndef MANAGE_DIR_H
# define MANAGE_DIR_H

int		list_dir_entries(char *path, size_t pathlen, const fopts_t *fopts, const dopts_t *dopts,
	bool print_path, bool print_nl, bool recursive);
void	append_filename(char *path, size_t pathlen, char *filename);

#endif //MANAGE_DIR_H
