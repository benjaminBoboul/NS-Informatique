cmake_minimum_required(VERSION 3.14)
project(Library C)

set(CMAKE_C_STANDARD 99)

add_executable(Library book.c bookArray.c CuTest.c bookArrayTest.c)