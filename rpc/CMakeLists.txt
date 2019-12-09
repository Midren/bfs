cmake_minimum_required(VERSION 3.14)
project(rpc)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CmakeConfig)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost COMPONENTS locale)
find_package(CryptoPP REQUIRED)

include_directories(${Boost_INCLUDE_DIR} ${CRYPTOPP_INCLUDE_DIR})

add_executable(rpc main.cpp rpc.cpp rpc.h encode.h encode.cpp)

target_link_libraries(rpc LINK_PUBLIC ${Boost_LIBRARIES} ${CRYPTOPP_LIBRARIES})