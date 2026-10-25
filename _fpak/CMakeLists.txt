# _fpak/CMakeLists.txt - build all the apps in one go
#                        (app dirs are siblings of _fpak)
cmake_minimum_required(VERSION 3.31)
project(swall LANGUAGES CXX)

foreach(d ftx big flatten l ned recent renem undup)
   add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../${d} ${d})
endforeach()
