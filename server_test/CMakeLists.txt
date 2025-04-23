cmake_minimum_required(VERSION 3.24)
project(server_test CXX)

# Include ISCE system
include(${CMAKE_SOURCE_DIR}/isce/isce.cmake)

file(GLOB SRC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILE})

target_include_directories(${PROJECT_NAME}
                           PUBLIC ${ISCE_INCLUDE})

target_link_libraries(${PROJECT_NAME} ${ISCE_LIBRARY})
