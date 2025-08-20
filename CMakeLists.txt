cmake_minimum_required(VERSION 3.10)

project(CppTestApi)

find_package(cpprestsdk CONFIG REQUIRED)

add_executable(CppTestApi main.cpp src/HttpServer.cpp src/Model/TestJson.cpp)

target_link_libraries(CppTestApi PRIVATE cpprestsdk::cpprest)