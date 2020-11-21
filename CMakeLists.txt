cmake_minimum_required(VERSION 3.0)
project(gtk_example)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_executable(example-0 example-0.c)
target_include_directories(example-0 PUBLIC ${GTK3_INCLUDE_DIRS})
target_link_libraries(example-0 ${GTK3_LIBRARIES})

add_executable(example-1 example-1.c)
target_include_directories(example-1 PUBLIC ${GTK3_INCLUDE_DIRS})
target_link_libraries(example-1 ${GTK3_LIBRARIES})
