#ifndef RPC_BFS_FUSE_H
#define RPC_BFS_FUSE_H

#include <cstdlib>

int bfs_read(const char *path, char *buf, size_t size, off_t offset);

int bfs_write(const char *path, const char *data, size_t size, off_t offset);

int bfs_create_file(const char *path, mode_t mode, dev_t dev);

int bfs_mkdir(const char *path, mode_t);

#endif //RPC_BFS_FUSE_H
