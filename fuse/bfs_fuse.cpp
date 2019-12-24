#include "bfs_fuse.h"
#include <fuse.h>
#include "../rpc/rpc.h"

static Rpc RPC{"0x00c469eee8b9bc1a331070be0e5814a0bc6f902e", "0x3fDCC710BA867541a2031c25bed49fdA04C2D1b7"};

int bfs_read(const char *path, char *buf, size_t size, off_t offset) {
    return RPC.read_file(path, reinterpret_cast<uint8_t *>(buf), size, offset);
}

int bfs_write(const char *path, const char *data, size_t size, off_t offset) {
    return RPC.write_file(path, reinterpret_cast<const uint8_t *>(data), size); // TODO: Add offset
}

int bfs_create_file(const char *path, mode_t mode, dev_t dev) {
    return RPC.create_file(path);
}

int bfs_mkdir(const char *path, mode_t) {
    return RPC.create_dir(path);
}

struct fuse_operations bfs_operations = {
        .open = [](const char *, int) { return 0; }, // We don`t need to open a file in BFS, TODO: Check if file exists
        .mknod = bfs_create_file,
        .read = bfs_read,
        .write = bfs_write,
        .mkdir = bfs_mkdir
};

int bfs_main(int argc, char *argv[]) {
    if ((getuid() == 0) || (geteuid() == 0)) {
        std::cout << "[WARNING]:\t Running as root!" << std::endl;
    }
    if (argc != 3) {
        throw std::invalid_argument("Invalid arguments.\n\tBFS [root_directory] [mount_point]");
    }
    return fuse_main(argc, argv, &bfs_operations);
}