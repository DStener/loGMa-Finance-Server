cmake_minimum_required(VERSION 3.24)
project(isce CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost COMPONENTS json url REQUIRED)
find_package(PostgreSQL REQUIRED)

file(GLOB SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/src/*.cc)
add_library(${PROJECT_NAME} ${SRC_DIR})


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/include
                                                   ${CMAKE_CURRENT_SOURCE_DIR}/include
                                                   ${Boost_INCLUDE_DIR};
                                                   ${PostgreSQL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES}
                                              PostgreSQL::PostgreSQL)