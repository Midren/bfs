#include <iostream>
#include "rpc.h"

int main() {
    Rpc rpc("0x00c469eee8b9bc1a331070be0e5814a0bc6f902e", "0x3fDCC710BA867541a2031c25bed49fdA04C2D1b7");
//    rpc.create_file("/some_file.txt");
    uint8_t data[1024] = {0xFF, 0xFE};
    std::cout << rpc.create_file("/hello.txt") << std::endl;
//    rpc.write_file("/test.txt", data, 2);
//    size_t num = rpc.read_file("/test.txt", data, 1024, 1);
//    std::cout << "0x";
//    for (int i = 0; i < num; i++) {
//        std::cout << std::hex << (unsigned int) data[i];
//    }
    return 0;
}