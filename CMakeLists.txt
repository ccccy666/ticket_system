cmake_minimum_required(VERSION 3.16)
project(code)

set(CMAKE_CXX_STANDARD 14)

add_executable(code main.cpp Train.h Account.h b+tree.h b+tree__.h Token_scanner.h exceptions.hpp utility.hpp vector.hpp map.hpp list.h)
