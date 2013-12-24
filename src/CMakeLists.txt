# Raspboop CMake file

cmake_minimum_required(VERSION 2.8)

# Raspboop Modules

set(MODULES
  boards/L298N
  interfaces/GPIOConsumer
  interfaces/Sensor
  sensors/HCSR04
  sensors/HCSR501
)

set(HEADERS
  ${CMAKE_SOURCE_DIR}/include/raspboop/Raspboop
)

foreach(module ${MODULES})
  list(APPEND HEADERS ${CMAKE_SOURCE_DIR}/include/raspboop/${module})
endforeach(module)

add_library(raspboop ${MODULES} ${HEADERS})
