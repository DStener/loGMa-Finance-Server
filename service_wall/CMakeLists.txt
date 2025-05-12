cmake_minimum_required(VERSION 3.24)
project(service_wall CXX)

# Include ISCE system
include(${CMAKE_SOURCE_DIR}/isce/isce.cmake)

file(GLOB_RECURSE SERVICE_SRC "*.cc" "*.h")
add_executable(${PROJECT_NAME} ${SERVICE_SRC})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.inc config.h @ONLY)

add_subdirectory(${CMAKE_SOURCE_DIR}/isce CMAKE_CURRENT_BINARY_DIR)

target_include_directories(${PROJECT_NAME}
                           PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
                                  ${CMAKE_CURRENT_SOURCE_DIR}
                                  ${CMAKE_CURRENT_SOURCE_DIR}/migration
                                  ${CMAKE_CURRENT_SOURCE_DIR}/seeders
                                  ${CMAKE_CURRENT_SOURCE_DIR}/dto
                                  ${CMAKE_CURRENT_SOURCE_DIR}/controllers
                                  ${CMAKE_CURRENT_SOURCE_DIR}/systems
                                  ${ISCE_INCLUDE})

target_link_libraries(${PROJECT_NAME} ${ISCE_LIBRARY} isce)
