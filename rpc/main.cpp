#include <iostream>
#include "rpc.h"

int main() {
    Rpc rpc("0x00c469eee8b9bc1a331070be0e5814a0bc6f902e", "0x3609d7BF7488b1Ca68D854Cb2184d40eBcA51E0a");
//    uint8_t data[1024] = {0xFF, 0xFF};
//    if(!rpc.create_file("/test.txt")) {
//        std::cout << "Couldn't create file" << std::endl;
//    }
//    if(!rpc.write_file("/test.txt", data, 2)) {
//        std::cout << "Couldn't write to a file" << std::endl;
//    }
//    size_t num = rpc.read_file("/test.txt", data, 1024, 0);
//    std::cout << "0x";
//    for (int i = 0; i < num; i++) {
//        std::cout << std::hex << (unsigned int) data[i];
//    }
    if(!rpc.create_dir("/etc")) {
        std::cout << "Couldn't create directory" << std::endl;
    }
    if(!rpc.create_dir("/etc/a")) {
        std::cout << "Couldn't create directory" << std::endl;
    }
    if(!rpc.create_dir("/etc/b")) {
        std::cout << "Couldn't create directory" << std::endl;
    }
//    for(auto &i: rpc.list_dir("/etc")) {
//        std::cout << i << std::endl;
//    }
    return 0;
}