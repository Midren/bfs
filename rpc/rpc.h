#ifndef RPC_RPC_H
#define RPC_RPC_H

#include <string>
#include <vector>

class rpc {
public:

    rpc() {

    }

    /* Work with files */

    int create_file(std::string path);

    int write_file(std::string path, uint8_t *bytes, size_t length);

    int read_file(std::string path, uint8_t *buf, size_t buf_size);

    ssize_t get_file_size(std::string path);

    int remove_file(std::string path);

    /* Work with directories */

    int create_dir(std::string path);

    std::vector<std::string> list_dir(std::string path);

    int remove_dir(std::string path);

private:
};


#endif //RPC_RPC_H
