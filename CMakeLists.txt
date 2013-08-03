cmake_minimum_required(VERSION 2.8)
project(ftprinter)

set(CMAKE_CXX_FLAGS "-pipe -pedantic -Wextra -Wno-unused-parameter --std=c++0x")

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/FTPrinter.cpp
    src/BufferedFTPrinter.cpp
    src/PrintFormat.cpp
    src/Table.cpp )

set(HEADER
    include/ftprinter/FTPrinter.h
    include/ftprinter/BufferedFTPrinter.h
    include/ftprinter/PrintFormat.h
    include/ftprinter/Table.h )

add_library(ftprinter STATIC ${SOURCES} )

add_executable(ftprinterTest src/test_main.cpp)
target_link_libraries(ftprinterTest ftprinter)
