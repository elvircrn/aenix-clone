cmake_minimum_required(VERSION 3.15)
project(os)

set(CMAKE_C_STANDARD 11)

file(GLOB source_files "*.c" "include/*.h" "*.o")
include_directories(include)

add_executable(os kmain.c ${source_files} include/slib.h slib.c include/console.h console.c include/rangeutil.h include/segmentation.h)