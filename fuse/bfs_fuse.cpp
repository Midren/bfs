#include "bfs_fuse.h"
#include "../rpc/rpc.h"

//static Rpc RPC{"0x00c469eee8b9bc1a331070be0e5814a0bc6f902e", "0xdd8ac7f9f50e465bac369dffabc978ec04183825"};
static Rpc *RPC = nullptr;

int bfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *) {
    return RPC->read_file(path, reinterpret_cast<uint8_t *>(buf), size, offset);
}

int bfs_write(const char *path, const char *data, size_t size, off_t offset, struct fuse_file_info *) {
    if (RPC->write_file(path, reinterpret_cast<const uint8_t *>(data), size)) // TODO: Add offset
        return size;
    return 0;
}

int bfs_create_file(const char *path, mode_t mode, dev_t dev) {
    return RPC->create_file(path);
}

int bfs_mkdir(const char *path, mode_t) {
    std::cout << "[DEBUG]" << path << std::endl;
    return RPC->create_dir(path);
}

int bfs_opendir(const char *path, struct fuse_file_info *) {
    return 0; // TODO: Check directory existence and permissions
}

int bfs_open(const char *path, struct fuse_file_info *fileInfo) {
    // TODO: if not exists create else return 0
    return 0; // TODO: Check if file exists, permissions
}

int bfs_readdir(const char *path, void *buff, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fileInfo) {
    std::cout << "[DEBUG] [READDIR] " << path << std::endl;
    std::vector<std::string> dirEntries = RPC->list_dir(path);
    dirEntries.emplace_back(".");
    dirEntries.emplace_back("..");
    for (const auto &entry:dirEntries) {
        if (filler(buff, entry.data(), nullptr, 0) != 0)
            return -EXIT_FAILURE;
    }
    return 0;
}

int bfs_getattr(const char *path, struct stat *stbuf) {
    if (strcmp(path, ".") != 0 && strcmp(path, "..") != 0 && strcmp(path, "/") != 0) {
        RPC->get_stat(path, stbuf);
        if (stbuf->st_mode == 0)
            stbuf = nullptr;
        return 0;
    }
    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
        return 0;
    }
    stbuf->st_mode = S_IFREG | 0777;
    stbuf->st_nlink = 1;
    return 0;
}

void *bfs_init(struct fuse_conn_info *conn) {
    return 0;
}

void bfs_destroy(void *) {
}

int bfs_unlink(const char *path) {
    return RPC->remove_file(path);
}

int bfs_rmdir(const char *path) {
    return RPC->remove_dir(path);
}


struct fuse_operations bfs_operations = {
        .getattr = bfs_getattr,
        .mknod = bfs_create_file,
        .mkdir = bfs_mkdir,
        .unlink = bfs_unlink,
        .rmdir = bfs_rmdir,
        .open = bfs_open, // We don`t need to open a file in BFS
        .read = bfs_read,
        .write = bfs_write,
        .opendir = bfs_opendir,
        .readdir = bfs_readdir,
        .init = bfs_init,
        .destroy = bfs_destroy
};

int main(int argc, char *argv[]) {
    if ((getuid() == 0) || (geteuid() == 0)) {
        std::cout << "[WARNING]:\t Running as root!" << std::endl;
    }
    if (argc < 4) {
        std::cerr << "Usage: BFS [mountpoint] [Used Address] [Memory Manager Address]" << std::endl;
    }
    RPC = new Rpc{argv[3], argv[4]};
    argc -= 2;
    return fuse_main(argc, argv, &bfs_operations, nullptr);
}