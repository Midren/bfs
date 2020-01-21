#include <iostream>
#include <sys/stat.h>
#include "rpc.h"

int main() {
    Rpc rpc("0x00c469eee8b9bc1a331070be0e5814a0bc6f902e", "0x50894efcabc8261df7ad1eb0923b7a401f33c522");
    uint8_t data[1024] = {0xAB, 0xBA};
    if (!rpc.create_file("/test.txt")) {
        std::cerr << "Couldn't create file" << std::endl;
    }
    if (!rpc.write_file("/test.txt", data, 2)) {
        std::cerr << "Couldn't write to a file" << std::endl;
    }
    std::cout << rpc.get_file_size("/test.txt") << std::endl;
    size_t num = rpc.read_file("/test.txt", data, 1024, 0);
    std::cout << "0x";
    for (int i = 0; i < num; i++) {
        std::cerr << std::hex << (unsigned int) data[i];
    }
    std::cout << std::endl;
    if (!rpc.create_dir("/etc")) {
        std::cerr << "Couldn't create directory" << std::endl;
    }
    if (!rpc.create_dir("/etc/file1")) {
        std::cerr << "Couldn't create directory" << std::endl;
    }
    if (!rpc.create_dir("/etc/file2")) {
        std::cerr << "Couldn't create directory" << std::endl;
    }
    std::cout << "Directory /etc/ has next files: " << std::endl;
    for (auto &i: rpc.list_dir("/etc/")) {
        std::cout << i << std::endl;
    }
    auto *st = new(struct stat);
    rpc.get_stat("/etc", st);
    std::cout << "Mode for directory: " << st->st_mode << std::endl;
    rpc.get_stat("/test.txt", st);
    std::cout << "Mode for file: " << st->st_mode << std::endl;
    std::cout << "Size of file: " << st->st_size << std::endl;
    delete (st);
    if(!rpc.remove_file("/test.txt")){
        std::cerr << "Couldn't delete test.txt" << std::endl;
    }
    return 0;
}