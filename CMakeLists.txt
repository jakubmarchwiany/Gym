cmake_minimum_required(VERSION 3.17)
project(untitled3)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled3 main.cpp client.cpp client.h gym.cpp gym.h reception.cpp reception.h sync_channel.cpp sync_channel.h place_in_line.cpp place_in_line.h screen_printer.cpp screen_printer.h receptionist.cpp receptionist.h)