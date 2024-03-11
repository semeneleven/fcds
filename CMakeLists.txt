cmake_minimum_required(VERSION 3.24)

project(fcds)

set(CMAKE_CXX_STANDARD 23)

set(SRC src/main.cc
        src/network/http.cc
        src/network/utils.cc)

add_executable(fcds ${SRC})   

find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost not found")
endif()

target_link_libraries(fcds PRIVATE Boost::boost)