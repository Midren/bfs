#include <iostream>
#include "rpc.h"
#include "encode.h"

int main() {
    std::string func("baz(string,byte[])");
    std::vector<byte> bytes = {0x48, 0x65, 0x6c, 0x6c};
    auto str = encode(func, std::string("Hello, world!"), bytes);
    Rpc rpc{};
    rpc.create_file("/home/midren/some_file.txt");
//    std::cout << to_string(str);
    return 0;
}