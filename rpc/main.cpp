#include <iostream>
#include "rpc.h"
#include "encode.h"

int main() {
    bytes bt = {0x48, 0x65, 0x6c, 0x6c};
    Rpc rpc{bt};
//    rpc.create_file("/some_file.txt");
    uint8_t data[1024];
    rpc.read_file("/usr", data, 1024);
    return 0;
}