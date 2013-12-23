cmake_minimum_required (VERSION 2.8)
project(RaspbOOP-Bot)

# Version
set(RaspbOOP-Bot_VERSION_MAJOR 0)
set(RaspbOOP-BOT_VERSION_MINOR 0)

set(SRC_FILES_DIR ${RASPBOOP-BOT_SOURCE_DIR}/src/)
set(INCLUDE_FILES_DIR ${RASPBOOP-BOT_SOURCE_DIR}/include/raspboop/)
set(CMAKE_INCLUSION ${RASPBOOP-BOT_CMAKE_DIR}/cmake)

set(RASPOOP-BOT_TARGET RaspOOP-Bot)

####################################
# Require wiringPi
####################################

find_library(WIRINGPI_LIB wiringPi)

set(RASBPOOP-BOT_FILES
  boards/L298N
  sensors/HCSR04
  sensors/HCSR501
)

foreach(rasbpoop_file ${RASBPOOP-BOT_FILES})
  list(APPEND SOURCE_FILES ${SRC_FILES_DIR}/${raspboop_file}.cpp)
  list(APPEND INCLUDE_FILES ${INCLUDE_FILES_DIR}/${raspboop_file}.h)
endforeach()

# Append common header to INCLUDE_FILES

# Append interfaces to INCLUDE_FILES

include_directories(
  ${X11_INCLUDE_DIR}
  ${X11_LIBRARIES_DIR}
  ${INCLUDE_FILES_DIR}
  )

add_library(${RASPBOOP-BOT_TARGET} STATIC ${SOURCE_FILES}
  ${INCLUDE_FILES})

target_link_libraries(${RASPBOOP-BOT_TARGET} ${X11_LIBRARIES}
  ${WIRINGPI_LIB})
