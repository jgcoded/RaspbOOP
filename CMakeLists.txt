cmake_minimum_required (VERSION 2.8)
project(RBP)

# Version
set(RBP_VERSION_MAJOR 0)
set(RBP_VERSION_MINOR 1)

set(RBP_TARGET RBP)

set(RBP_BIN_DIR ${PROJECT_SOURCE_DIR}/bin/)
set(RBP_LIB_DIR ${PROJECT_SOURCE_DIR}/lib/)
set(RBP_INC_DIR ${PROJECT_SOURCE_DIR}/include/)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RBP_LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RBP_BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RBP_BIN_DIR})
  
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BUILD_SHARED_LIBS
    "Build RBP as a shared library." ON)

option(RBP_BUILD_TESTS "Build the RBP tests " ON)

option(INSTALL_SDK "Install the RBP sdk" ON)

set(INSTALL_DIR "/opt/RBP/" CACHE PATH "The installation directory")
set(CMAKE_INSTALL_PREFIX ${INSTALL_DIR})

# Unix setup

set(CMAKE_CXX_FLAGS "-std=c++0x")

find_package(X11 REQUIRED)

# System and regex are required for boost.asio
find_package(Boost 1.56 COMPONENTS system regex REQUIRED)

include_directories(
  ${X11_INCLUDE_DIR}
  ${X11_LIBRARIES_DIR}
  ${Boost_INCLUDE_DIR}
)

# Submodules

# WiringPi
set(WPI_TARGET ${CMAKE_SOURCE_DIR}/wiringPi)

find_library(WIRINGPI wiringPi PATHS ${WPI_TARGET}/wiringPi)

if(EXISTS ${WPI_TARGET} AND WIRINGPI_NOTFOUND)
  message(STATUS "Using wiringPi submodule")

  execute_process(COMMAND make WORKING_DIRECTORY ${WPI_TARGET}/wiringPi OUTPUT_QUIET)
  execute_process(COMMAND ln -s libwiringPi.so.1.0 libwiringPi.so.1 WORKING_DIRECTORY ${WPI_TARGET}/wiringPi OUTPUT_QUIET)
  execute_process(COMMAND ln -s libwiringPi.so.1.0 libwiringPi.so WORKING_DIRECTORY ${WPI_TARGET}/wiringPi OUTPUT_QUIET)

  find_library(WIRINGPI wiringPi PATHS ${WPI_TARGET}/wiringPi)
endif()

message(STATUS "Using wiringPi library: ${WIRINGPI}")

set(RBP_LIBRARIES
  ${X11_LIBRARIES}
  ${WIRINGPI}
  ${Boost_LIBRARIES}
  pthread
)

# RBP include paths

include_directories(
  ${RBP_INC_DIR}
)

# RBP CMake Subdirectories

add_subdirectory(src)

if(RBP_BUILD_TESTS)
  add_subdirectory(test)
endif()
