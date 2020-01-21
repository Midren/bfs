cmake_minimum_required(VERSION 3.14)
project(rpc)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CmakeConfig)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FILE_OFFSET_BITS=64")
find_package(Boost COMPONENTS locale)
find_package(CryptoPP REQUIRED)
find_package(CURL REQUIRED)
find_package(FUSE REQUIRED)

include_directories(${Boost_INCLUDE_DIR} ${CRYPTOPP_INCLUDE_DIR} ${CURL_INCLUDE_DIR} ${FUSE_INCLUDE_DIRS})
add_library(rpc-library rpc/rpc.h rpc/encode.h rpc/encode.cpp rpc/curl_wrapper.cpp rpc/curl_wrapper.h rpc/decode.cpp rpc/decode.h)
target_link_libraries(rpc-library LINK_PUBLIC ${Boost_LIBRARIES} ${CRYPTOPP_LIBRARIES} ${CURL_LIBRARIES})

add_executable(test-rpc rpc/main.cpp)
target_link_libraries(test-rpc LINK_PUBLIC rpc-library)

add_executable(BFS fuse/bfs_fuse.cpp)
target_link_libraries(BFS LINK_PUBLIC rpc-library ${FUSE_LIBRARIES})
