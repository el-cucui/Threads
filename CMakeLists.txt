cmake_minimum_required(VERSION 3.15)

PROJECT(Threads VERSION 1.0
    DESCRIPTION "Threads"
    LANGUAGES CXX)
ADD_EXECUTABLE(simple_thread simple_thread.cpp)
ADD_EXECUTABLE(simple_lock simple_locks.cpp)
ADD_EXECUTABLE(simple_cond simple_cond.cpp)