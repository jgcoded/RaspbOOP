cmake_minimum_required (VERSION 2.8)
project(RaspOOP-Bot)

# Version
set(RaspOOP-Bot)

set(SRC_FILES_DIR ${RASPOOP-BOT_SOURCE_DIR}/src)
set(INCLUDE_FILES_DIR ${RASPOOP-BOT_SOURCE_DIR}/include)
set(CMAKE_INCLUSION ${RASPOOP-BOT_CMAKE_DIR}/cmake)

set(RASPOOP-BOT_TARGET RaspOOP-Bot)

####################################
# Require wiringPi
####################################

find_library(WIRINGPI_LIB wiringPi)

set(RASPOOP-BOT_FILES

)

foreach(raspoop_file ${RASPOOP-BOT_FILES})
  list(APPEND SOURCE_FILES ${SRC_FILES_DIR}/${raspoop_file}.cpp)
  list(APPEND INCLUDE_FILES ${INCLUDE_FILES_DIR}/${raspoop_file}.h)
endforeach()

include_directories(
  ${X11_INCLUDE_DIR}
  ${X11_LIBRARIES_DIR}
  ${INCLUDE_FILES_DIR}
  )

add_library(${RASPOOP-BOT_TARGET} ${LIB_TYPE} ${SOURCE_FILES}
  ${INCLUDE_FILES})

target_link_libraries(${RASPOOP-BOT_TARGET} ${X11_LIBRARIES} ${wiringPi})
