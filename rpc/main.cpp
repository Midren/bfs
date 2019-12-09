#include <iostream>
#include "rpc.h"
#include "encode.h"
#include <curl/curl.h>

int main() {
    std::string func("baz(string,byte[])");
    bytes bt = {0x48, 0x65, 0x6c, 0x6c};
    auto str = encode(func, std::string("Hello, world!"), bt);
    Rpc rpc{bt};
    rpc.create_file("/some_file.txt");
    std::cout << to_string(str);
    return 0;
}