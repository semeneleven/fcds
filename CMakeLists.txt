cmake_minimum_required(VERSION 3.24)

project(fcds)

set(CMAKE_CXX_STANDARD 23)

set(SRC src/main.cc)

add_executable(fcds ${SRC})   

find_package(CURL REQUIRED)
if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "CURL not found")
endif()

target_link_libraries(fcds PRIVATE CURL::libcurl)