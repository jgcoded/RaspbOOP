cmake_minimum_required (VERSION 2.8)
project(Raspboop)

# Version
set(RASPBOOP-BOT_VERSION_MAJOR 0)
set(RASPBOOP-BOT_VERSION_MINOR 0)

set(RASPBOOP_TARGET raspboop)

####################################
# Require wiringPi
####################################

find_library(WIRINGPI wiringPi)
  
option(BUILD_SHARED_LIBS
    "Build Raspboop as a shared library." ON)

option(RASPBOOP_BUILD_TESTS "Build the Raspboop tests " ON)

# Unix setup

find_package(X11 REQUIRED)
include_directories(
  ${X11_INCLUDE_DIR}
  ${X11_LIBRARIES_DIR}
)

set(RASPBOOP_LIBRARIES
  ${X11_LIBRARIES}
  ${WIRINGPI}
)

# Raspboop include/lib paths

include_directories(
  ${CMAKE_SOURCE_DIR}/include
)

link_directories(${CMAKE_SOURCE_DIR}/include)

# Raspboop CMake Subdirectories

add_subdirectory(src)

if(RASPBOOP_BUILD_TESTS)
  add_subdirectory(test)
endif()
