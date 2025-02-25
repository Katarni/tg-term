cmake_minimum_required(VERSION 3.28.1)
project(tg-term)

set(CMAKE_C_STANDARD 23)
#set(CMAKE_OSX_ARCHITECTURES "x86_64")

add_executable(tg-term
                 main.c
                 include/tg-client.h
                 source/tg-client.c
)

find_package(json-c CONFIG)
find_package(Curses REQUIRED)
find_package(Td REQUIRED)
find_package(OpenSSL REQUIRED)
target_link_libraries(tg-term PRIVATE
                             Td::TdJsonStatic 
                             json-c::json-c 
                             Curses
                             OpenSSL::SSL
                             OpenSSL::Crypto
)
