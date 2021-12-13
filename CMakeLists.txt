cmake_minimum_required(VERSION 3.16)
project(airplane1 C)

set(CMAKE_C_STANDARD 99)

add_executable(airplane1 main.c datetime.c datetime.h airplane.c airplane.h queue.c queue.h)
