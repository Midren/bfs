#include <iostream>
#include "rpc.h"

int main() {
    Rpc rpc("0x00c469eee8b9bc1a331070be0e5814a0bc6f902e", "0x924b6A5A9519BCB915965999950F1ACaB0a832a2");
    uint8_t data[1024] = {0xAB, 0xBA};
    if(!rpc.create_file("/test.txt")) {
        std::cout << "Couldn't create file" << std::endl;
    }
    if(!rpc.write_file("/test.txt", data, 2)) {
        std::cout << "Couldn't write to a file" << std::endl;
    }
    std::cout << rpc.get_file_size("test.txt") << std::endl;
    size_t num = rpc.read_file("/test.txt", data, 1024, 0);
    std::cout << "0x";
    for (int i = 0; i < num; i++) {
        std::cout << std::hex << (unsigned int) data[i];
    }
    std::cout << std::endl;
    if(!rpc.create_dir("/etc")) {
        std::cout << "Couldn't create directory" << std::endl;
    }
    if(!rpc.create_dir("/etc/file1")) {
        std::cout << "Couldn't create directory" << std::endl;
    }
    if(!rpc.create_dir("/etc/file2")) {
        std::cout << "Couldn't create directory" << std::endl;
    }
    std::cout << "Directory /etc/ has next files: " << std::endl;
    for(auto &i: rpc.list_dir("/etc/")) {
        std::cout << i << std::endl;
    }
    return 0;
}