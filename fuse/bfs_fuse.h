#ifndef RPC_BFS_FUSE_H
#define RPC_BFS_FUSE_H

#include <cstdlib>

#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <sys/stat.h>


int bfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *);

int bfs_write(const char *path, const char *data, size_t size, off_t offset,struct fuse_file_info *);

int bfs_create_file(const char *path, mode_t mode, dev_t dev);

int bfs_mkdir(const char *path, mode_t);

int bfs_opendir(const char *path, struct fuse_file_info *);

int bfs_open(const char *path, struct fuse_file_info *fileInfo);

int bfs_readdir(const char *path, void *buff, fuse_fill_dir_t filler, off_t offset,
                struct fuse_file_info *fileInfo);

int bfs_getattr(const char *path, struct stat *st);

void *bfs_init(struct fuse_conn_info *conn);

void bfs_destroy(void *);
int bfs_unlink(const char *path);
int bfs_rmdir(const char* path);
#endif //RPC_BFS_FUSE_H
