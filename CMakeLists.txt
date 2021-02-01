cmake_minimum_required(VERSION 3.16)
project(tiny_json C)

set(CMAKE_C_STANDARD 99)

#add_executable(tiny_json main.c unit_test.c json.c json.h json_dev.c json_dev.h token_link_list.c token_link_list.h tokenizer.c tokenizer.h)

add_library(tiny_json SHARED json.c json.h json_dev.c json_dev.h token_link_list.c token_link_list.h tokenizer.c tokenizer.h)