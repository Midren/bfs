#include <iostream>
#include "rpc.h"
#include "encode.h"

int main() {
    std::string func("baz(string,byte[])");
    std::vector<byte> bytes = {0x48, 0x65, 0x6c, 0x6c};
    auto str = encode(func, std::string("Hello, world!"), bytes);
    std::cout << to_string(str);
//    int q = 0;
//    for (auto i: str) {
//        if (q % 32 == 0)
//            printf("\n");
//        printf("%02x", i);
//        q++;
//    }
    return 0;
}