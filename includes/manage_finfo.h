#ifndef MANAGE_FINFO_H
# define MANAGE_FINFO_H

int		fill_finfo(const char *path, char *name, const fopts_t *opts, finfo_t *finfo);
void	update_dinfo(dinfo_t *max_dinfo, const dinfo_t *file_dinfo);

#endif //MANAGE_FINFO_H
