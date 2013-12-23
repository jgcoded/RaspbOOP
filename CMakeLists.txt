cmake_minimum_required (VERSION 2.8)
project(Raspboop)

# Version
set(RASPBOOP-BOT_VERSION_MAJOR 0)
set(RASPBOOP-BOT_VERSION_MINOR 0)

set(SRC_FILES_DIR ${CMAKE_SOURCE_DIR}/src/)
set(INCLUDE_FILES_DIR ${CMAKE_SOURCE_DIR}/include/raspboop/)

set(RASPBOOP-BOT_TARGET raspboop)

####################################
# Require wiringPi
####################################
set(WIRINGPI wiringPi)
add_library(${WIRINGPI} SHARED IMPORTED)
set_target_properties(${WIRINGPI} PROPERTIES IMPORTED_LOCATION
  /usr/local/lib/libwiringPi.so)

set(RASPBOOP-BOT_FILES
  boards/L298N
  sensors/HCSR04
  sensors/HCSR501
)

foreach(raspboop_file ${RASPBOOP-BOT_FILES})
  list(APPEND SOURCE_FILES ${SRC_FILES_DIR}/${raspboop_file}.cpp)
  list(APPEND INCLUDE_FILES ${INCLUDE_FILES_DIR}/${raspboop_file}.h)
endforeach()

# Append common header to INCLUDE_FILES

# Append interfaces to INCLUDE_FILES

include_directories(
  ${X11_INCLUDE_DIR}
  ${X11_LIBRARIES_DIR}
  ${CMAKE_SOURCE_DIR}/include
  )

add_library(${RASPBOOP-BOT_TARGET} STATIC ${SOURCE_FILES} ${INCLUDE_FILES})

target_link_libraries(${RASPBOOP-BOT_TARGET} ${X11_LIBRARIES} ${WIRINGPI})
