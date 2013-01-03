cmake_minimum_required(VERSION 2.8)
project(ftprinter)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(ftprinter STATIC
  include/ftprinter/FTPrinter.h
  src/FTPrinter.cpp
  include/ftprinter/PrintFormat.h
  src/PrintFormat.cpp
)

add_executable(ftprinterTest src/test_main.cpp)
target_link_libraries(ftprinterTest ftprinter)
