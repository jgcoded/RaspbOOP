cmake_minimum_required (VERSION 2.8)
project(RaspOOP-Bot)

# Version
set(RaspOOP-Bot)

set(SRC_FILES_DIR ${RASPOOP-BOT_SOURCE_DIR}/src)
set(INCLUDE_FILES_DIR ${RASPOOP-BOT_SOURCE_DIR}/include)
set(CMAKE_INCLUSION ${RASPOOP-BOT_CMAKE_DIR}/cmake)

####################################
# Require wiringPi
####################################

find_package(wiringPi)
