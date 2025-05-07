cmake_minimum_required(VERSION 3.24)
project(server_dev CXX)

# Include ISCE system
include(${CMAKE_SOURCE_DIR}/isce/isce.cmake)

set(BOOST_ALL_NO_LIB 1)

file(GLOB CONTROLLERS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/controllers/*.cc)
file(GLOB SYSTEM_SRC ${CMAKE_CURRENT_SOURCE_DIR}/systems/*.cc)
file(GLOB DIRECT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
add_executable(${PROJECT_NAME} ${DIRECT_SRC} ${CONTROLLERS_SRC} ${SYSTEM_SRC}   "migration/Schema.h")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.inc config.h @ONLY)

add_subdirectory(${CMAKE_SOURCE_DIR}/isce CMAKE_CURRENT_BINARY_DIR)

target_include_directories(${PROJECT_NAME}
                           PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
                                  ${CMAKE_CURRENT_SOURCE_DIR}
                                  ${CMAKE_CURRENT_SOURCE_DIR}/controllers
                                  ${CMAKE_CURRENT_SOURCE_DIR}/systems
                                  ${ISCE_INCLUDE})

target_link_libraries(${PROJECT_NAME} ${ISCE_LIBRARY} isce)
