cmake_minimum_required(VERSION 3.30)
project(Zadanie5 C)

set(CMAKE_C_STANDARD 99)

add_executable(Zadanie5 RBTree.c
        HashTable.c
        WBTree.c
        Tester.c
        RBTree.h
        HashTable.h)
