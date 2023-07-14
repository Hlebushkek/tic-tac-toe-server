cmake_minimum_required(VERSION 3.24)

project(tic-tac-toe-server)

enable_language(C)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(external)
file(GLOB SOURCES "source/*.cpp" "include/*.hpp" "external/net/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES})

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)
# set(Boost_DEBUG 1)

find_package(Boost REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()