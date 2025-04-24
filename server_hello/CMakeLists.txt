cmake_minimum_required(VERSION 3.24)
project(server_hello CXX)

# Include ISCE system
include(${CMAKE_SOURCE_DIR}/isce/isce.cmake)

set(BOOST_ALL_NO_LIB 1)

file(GLOB SRC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/controller/*.cc)
add_executable(${PROJECT_NAME} main.cc ${SRC_FILE})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.inc config.h @ONLY)


target_include_directories(${PROJECT_NAME}
                           PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
                                  ${CMAKE_CURRENT_SOURCE_DIR}
                                  ${CMAKE_CURRENT_SOURCE_DIR}/controller
                                  ${ISCE_INCLUDE})

target_link_libraries(${PROJECT_NAME} ${ISCE_LIBRARY})
