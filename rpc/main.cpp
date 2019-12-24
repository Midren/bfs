#include <iostream>
#include "rpc.h"
#include "encode.h"

int main() {
    bytes bt = {0x48, 0x65, 0x6c, 0x6c};
    Rpc rpc("0x00c469eee8b9bc1a331070be0e5814a0bc6f902e", "0x3fDCC710BA867541a2031c25bed49fdA04C2D1b7");
//    rpc.create_file("/some_file.txt");
    uint8_t data[1024] = {0xFF, 0xFF, 0xFF};
//    rpc.create_file("/hello.txt");
    rpc.write_file("/hello.txt", data, 3);
//    rpc.read_file("/hello.txt", data, 1024);
    return 0;
}