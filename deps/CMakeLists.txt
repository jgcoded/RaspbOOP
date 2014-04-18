cmake_minimum_required(VERSION 2.8)

# download wiringPi

set(WPI_MIRROR https://github.com/WiringPi/WiringPi/archive/master.zip)
set(WPI_TARGET ${CMAKE_SOURCE_DIR}/deps/WiringPi-master)
set(WPI_FILE ${WPI_TARGET}.zip)

if(NOT EXISTS ${WPI_FILE} AND NOT EXISTS ${WPI_TARGET})
  message(STATUS "  Downloading wiringPi")
  file(DOWNLOAD ${WPI_MIRROR} ${WPI_FILE} SHOW_PROGRESS)
endif()

if(NOT EXISTS ${WPI_TARGET} AND EXISTS ${WPI_FILE})
  message(STATUS "  Unpacking wiringPi")
  execute_process(COMMAND unzip ${WPI_FILE} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/deps OUTPUT_QUIET)
  message(STATUS "  Removing downloaded file")
  file(REMOVE ${WPI_FILE})
endif()

if(EXISTS ${WPI_TARGET})
  message(STATUS "  Using downloaded wiringPi library")

  if(NOT EXISTS ${WPI_TARGET}/wiringPi/libwiringPi.so)
    execute_process(COMMAND make WORKING_DIRECTORY ${WPI_TARGET}/wiringPi OUTPUT_QUIET)
    execute_process(COMMAND ln -s libwiringPi.so.1.0 libwiringPi.so.1 WORKING_DIRECTORY ${WPI_TARGET}/wiringPi OUTPUT_QUIET)
    execute_process(COMMAND ln -s libwiringPi.so.1.0 libwiringPi.so WORKING_DIRECTORY ${WPI_TARGET}/wiringPi OUTPUT_QUIET)
  endif()

  find_library(WIRINGPI wiringPi PATHS ${WPI_TARGET}/wiringPi)
endif()
