cmake_minimum_required(VERSION 3.24)

project(FCDS)

set(CMAKE_CXX_STANDARD 23)

set(SRC src/main.cc)

add_executable(FCDS ${SRC})

find_package(Boost REQUIRED)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found")
else()    
    include_directories(${Boost_INCLUDE_DIRS})
endif()    

target_link_libraries(FCDS PRIVATE ${Boost_LIBRARIES})