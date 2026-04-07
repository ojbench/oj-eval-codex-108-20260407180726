cmake_minimum_required(VERSION 3.10)
project(code CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(code main.cpp)

if (MSVC)
  target_compile_options(code PRIVATE /O2 /W4)
else()
  target_compile_options(code PRIVATE -O2 -pipe -static-libstdc++ -static-libgcc -Wall -Wextra -Wconversion -Wshadow -Wformat=2)
endif()

