cmake_minimum_required(VERSION 3.24)
project(isce CXX)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


file(GLOB SRC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_library(${PROJECT_NAME} ${SRC_FILE})

find_package(Boost REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARY_DIRS})

# External libraries
target_include_directories(${PROJECT_NAME}
						   PRIVATE ${Boost_INCLUDE_DIR})
# Our interface 
target_include_directories(${PROJECT_NAME}
						   PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/isce)