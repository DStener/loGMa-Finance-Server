cmake_minimum_required(VERSION 3.24)
project(server_test CXX)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


file(GLOB SRC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILE})

add_subdirectory(${CMAKE_SOURCE_DIR}/isce build)

target_include_directories(${PROJECT_NAME}
                           PUBLIC ${CMAKE_SOURCE_DIR}/isce/include)

target_link_libraries(${PROJECT_NAME} isce)
