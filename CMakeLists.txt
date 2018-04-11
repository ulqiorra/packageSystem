cmake_minimum_required(VERSION 3.9)
project(packageSystem)

include_directories(../packageSystem/3rdparty)

set(CMAKE_CXX_STANDARD 11)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")

add_executable(packageSystem source/main.cpp source/Package.cpp source/Package.h source/PackageController.cpp source/PackageController.h)