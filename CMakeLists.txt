cmake_minimum_required (VERSION 2.8)
project(Raspboop)

# Version
set(RASPBOOP_VERSION_MAJOR 0)
set(RASPBOOP_VERSION_MINOR 0)

set(RASPBOOP_TARGET raspboop)

set(RASPBOOP_BIN_DIR ${PROJECT_SOURCE_DIR}/bin/)
set(RASPBOOP_LIB_DIR ${PROJECT_SOURCE_DIR}/lib/)
set(RASPBOOP_INC_DIR ${PROJECT_SOURCE_DIR}/include/)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RASPBOOP_LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RASPBOOP_BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RASPBOOP_BIN_DIR})
  
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BUILD_SHARED_LIBS
    "Build Raspboop as a shared library." ON)

option(RASPBOOP_BUILD_TESTS "Build the Raspboop tests " ON)

option(INSTALL_SDK "Install the Raspboop sdk" ON)

set(INSTALL_DIR "/opt/raspboop/" CACHE FILEPATH "The installation directory")
set(CMAKE_INSTALL_PREFIX ${INSTALL_DIR})

# Unix setup

set(CMAKE_CXX_FLAGS "-std=c++0x")

find_package(X11 REQUIRED)
# System and regex are required for boost.asio
find_package(Boost 1.57 COMPONENTS system regex REQUIRED)

include_directories(
  ${X11_INCLUDE_DIR}
  ${X11_LIBRARIES_DIR}
  ${Boost_INCLUDE_DIR}
)

# Get dependencies
add_subdirectory(deps)

set(RASPBOOP_LIBRARIES
  ${X11_LIBRARIES}
  ${WIRINGPI}
  ${Boost_LIBRARIES}
  pthread
)

# Raspboop include paths

include_directories(
  ${CMAKE_SOURCE_DIR}/deps/WiringPi-master/wiringPi
  ${CMAKE_SOURCE_DIR}/include
)

# Raspboop CMake Subdirectories

add_subdirectory(src)
add_subdirectory(qt/RobotStation)

if(RASPBOOP_BUILD_TESTS)
  add_subdirectory(test)
endif()
